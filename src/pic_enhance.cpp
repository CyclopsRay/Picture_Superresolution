#include"pic_enhance.h"
#include"model_super_res.h"
#include"new_model.h"
#include"pic_enhance_module.h"

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <mutex>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"

#define VERSION_NUM "1.0"
#define PIC_LOG(x) 
#define SCALE 2  //the scale u want to zoom in
#define CLAP(a) (max((min(a, 0xff)), 0x00)) 
#define TFLITE_MINIMAL_CHECK(x)                              \
  if (!(x)) {                                                \
    fprintf(stderr, "Error at %s:%d\n", __FILE__, __LINE__); \
    exit(1);                                                 \
  }

#define RTN(x)                                              \
     m[hhash].second.unlock();                              \
     return (x);

#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif                                             

#define MOD 998244353
#define PRM1 1e5+7
#define PRM2 1e6+7
#define PRM3 1e7+7
#define PRM4 1e8+7
using namespace std;
#define SCALE 2
class Handle{
public:
    Handle(picInfo *p):pic(p){
        this->life=1;
    };
    picInfo *pic;
    int ehcType;
    std::unique_ptr<tflite::FlatBufferModel> model;
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    uint8_t *in_buf,*out_buf;
    long long  get_hash(){
        return ((int)(this->pic->format*PRM1+this->pic->w*PRM2+this->pic->h*PRM3+this->ehcType*PRM4))%MOD;
    };
    int life;
};
map < long long,pair < Handle *,mutex > > m;
int tell_the_version=1;


//---------------------------------------------------------------------------------------
void* OVision_Init(int enhance_type,picInfo *pic){
    //buffer create
    if(enhance_type>=OVISION_ENHANCE_END)return nullptr;
    Handle *handle=new Handle(pic);
    handle->ehcType=enhance_type;
    long long hhash=handle->get_hash();
    LOG("handle hash is %lld\n",hhash);
    if(m.find(handle->get_hash())!=m.end()){
        LOG("This handle has been created.\n");
        m[hhash].first->life++;
        return (void *)m[hhash].first;
    }
    //else
    m[hhash].first=handle;
    m[hhash].second.lock();
    //allocate
    switch(pic->format){
        case OVISION_NV12:
            handle->in_buf=handle->out_buf=nullptr;
        break;
        case OVISION_RGB:
            handle->in_buf=(uint8_t *)malloc(pic->h*pic->w*1.5);
            handle->out_buf=(uint8_t *)malloc(SCALE*SCALE*pic->h*pic->w*1.5);
        break;
        default:
        cout<<"Picture format error!"<<endl;
        RTN(nullptr);
    }
    LOG("Param accepted\n");
    if(tell_the_version--)cout<<"Ovision picture enhance SDK version: "<<VERSION_NUM<<endl;
    //load model
#ifdef NEW_MODEL
    handle->model=tflite::FlatBufferModel::BuildFromBuffer((const char *)(char *)new_model,new_model_len);
#else
    handle->model=tflite::FlatBufferModel::BuildFromBuffer((const char *)(char *)out_pb_tflite,out_pb_tflite_len);
#endif
    if(handle->model==nullptr){
        LOG("Model load failed!\n");
        RTN(nullptr);
    }
    tflite::InterpreterBuilder builder(*handle->model,handle->resolver);
    builder(&handle->interpreter);
    if(handle->interpreter==nullptr){
        LOG("Interpreter build failed!\n");
        RTN(nullptr);
    }
    vector<int> resize_input={1,pic->h,pic->w,1};
    int innum=handle->interpreter->inputs()[0];
    int outnum=handle->interpreter->outputs()[0];
    if(handle->interpreter->ResizeInputTensor(innum,resize_input) != kTfLiteOk){
        LOG("The size modification failed!\n");
        RTN(nullptr);
    }
    //cout<<"The node of the net has input (x) and output (y)"<<innum<<" "<<outnum<<endl;    
    if(handle->interpreter->AllocateTensors() != kTfLiteOk){
        LOG("The interpreter Allocation precess failed!\n");
        RTN(nullptr);
    }
    pic->h=pic->h*SCALE;
    pic->w=pic->w*SCALE;
    LOG("Ovision_init completed.\n");
    RTN((void *)handle);
}


//------------------------------------------------------------------------------------------
int OVision_Process(void *hhandle, uint8_t *input, uint8_t *output){
    // FILE *fd1=fopen("../d1.bin","wb");
    // FILE *fd2=fopen("../d2.bin","wb");
    Handle *handle=(Handle *)hhandle;
    long long hhash=handle->get_hash();
    m[hhash].second.lock();
    int format=handle->pic->format,h=handle->pic->h/SCALE,w=handle->pic->w/SCALE;
    //transfer all the type to NV12.
    switch (format)//calculate the size
    {
    case OVISION_RGB:
        BGR2NV12(input,handle->in_buf,w,h);
        break;
    case OVISION_NV12:
        break;
    default:
        break;
    }
    // fwrite(handle->in_buf,sizeof(uint8_t),w*h*1.5,fd1);
    // fclose(fd1);


    //for now on only NV12 permitted.
    switch(handle->ehcType){
        case OVISION_SUPER_RES:
            //NV12 form: input->output; Other: in_buf->out_buf 
            int flg;
            LOG("The input and output tensor is %d %d\n",handle->interpreter->inputs()[0],handle->interpreter->outputs()[0]);
            if(format==OVISION_NV12){
                flg=NV12Linear(input,output,w,h, handle->pic->w, handle->pic->h);
            }
            else{
                flg=NV12Linear(handle->in_buf,handle->out_buf,w,h, handle->pic->w, handle->pic->h);
            }
            if(flg)return OVISION_LINEAR_TRANS_FAILED;
            float* in=handle->interpreter->typed_input_tensor<float>(0);
            if(format==OVISION_NV12){
                for(int i=0;i<h*w;++i)in[i]=(float)input[i]/255;
            }
            else{
                for(int i=0;i<h*w;++i)in[i]=(float)handle->in_buf[i]/255;
            }
            LOG("Input seccess\n");
            if(handle->interpreter->Invoke()!= kTfLiteOk){
                LOG("RUN FAILED\n");
                return OVISION_TRANSFER_FAILED;
            }
            else {
                LOG("RUN SUCCESS\n");
            }    
            float* out=handle->interpreter->typed_output_tensor<float>(0);
            if(format==OVISION_NV12){
                for(int i=0;i<handle->pic->h*handle->pic->w;i++)output[i]=(uint8_t)Clap(out[i]*255);
            }
            else{
                for(int i=0;i<handle->pic->h*handle->pic->w;i++)handle->out_buf[i]=(uint8_t)Clap(out[i]*255);
            }
        break;
    }
    // fwrite(handle->out_buf,sizeof(uint8_t),handle->pic->w*handle->pic->h*1.5,fd2);
    // fclose(fd2);


    //transfer the NV12 to the demanded format, and fill in the output buffer.
    switch(format){
        case OVISION_NV12:
        break;
        case OVISION_RGB:
        NV122BGR(handle->out_buf,output,handle->pic->w,handle->pic->h);
        break;
    }
    LOG("Ovision process completed");
    m[hhash].second.unlock();
    return OVISION_ENHANCE_OK;
}


//------------------------------------------------------------------------------------
void OVision_Deinit(void *hhandle){
    Handle *handle=(Handle *)hhandle;
    m[handle->get_hash()].second.lock();
    if(handle==nullptr)return;
    if(--handle->life){
        m[handle->get_hash()].second.unlock();
        return;
    }
    free(handle->in_buf);
    free(handle->out_buf);
    m[handle->get_hash()].second.unlock();
    m.erase(handle->get_hash());
    LOG("Ovision deinit completed\n");
}
