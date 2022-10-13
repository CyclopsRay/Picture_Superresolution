#include"pic_enhance.h"
#include <iostream>
using namespace std;
#define CLAP(a) (max((min(a, 0xff)), 0x00)) 
int main(){
    FILE *fout=fopen("../out_final.bin","wb");
    FILE *fin=fopen("../in_nv.bin","rb");
    int in_h=700;//determined by the picture.
    int in_w=700;
    picInfo *pI=new picInfo(OVISION_NV12,in_h,in_w);
    void* handle=OVision_Init(OVISION_SUPER_RES,pI);
    int out_h=pI->h;
    int out_w=pI->w;
	uint8_t *in_nv12=(uint8_t *)malloc(in_h*in_w*1.5);
    uint8_t *out=(uint8_t *)malloc(out_h*out_w*1.5);
	fread(in_nv12,sizeof(uint8_t),in_h*in_w*1.5,fin);
    int flg=OVision_Process(handle,in_nv12,out);
    switch(flg){
        case OVISION_ENHANCE_OK:
            cout<<"DONE"<<endl;
        break;
        case OVISION_FILE_NOT_FOUND:
            cout<<"prob1"<<endl;
        break;
        case OVISION_MODEL_NOT_FOUND:
            cout<<"prob2"<<endl;
        break;
        case OVISION_TRANSFER_FAILED:
            cout<<"prob3"<<endl;
        break;
    }
    fwrite(out,sizeof(uint8_t),out_h*out_w*1.5,fout);
    OVision_Deinit(handle);
    delete pI;
}
//To see the picture, type:
//ffplay -pixel_format nv12 -f rawvideo -video_size 1400x1400 ${PROJECT_SOURCE_PATH}/project1/example/example_nv12/out_final.bin
//where ${PROJECT_SOURCE_PATH} is the place you put project1