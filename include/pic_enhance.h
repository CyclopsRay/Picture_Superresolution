#ifndef __PIC_ENHANCE_H_
#define __PIC_ENHANCE_H_

typedef unsigned char uint8_t;
enum{//enhance type
    OVISION_SUPER_RES=1,

    OVISION_ENHANCE_END,
    //
};
enum{//process fault
    OVISION_ENHANCE_OK=0,
    OVISION_FILE_NOT_FOUND=1,
    OVISION_MODEL_NOT_FOUND=2,
    OVISION_TRANSFER_FAILED=3,
    OVISION_LINEAR_TRANS_FAILED=4,
};
enum{//format
    OVISION_RGB=0,
    OVISION_NV12=1,
    //NV21,
    //YU12
    OVISION_FORMAT_END,
};
/*
to create it :
picInfo pI=new picInfo(NV12,700,700);
*/
class picInfo{
//you need to new an object to use it, and ensure this object exist till the Deinit func is called.
public:
    picInfo(){};
    picInfo(int f,int hh,int ww):format(f),h(hh),w(ww){
        
    }
    int format;//pick from the format enum
    int h,w;
};

/*
Init part, init the interpreter model and resovler, resize the input frame
*@param enhance_type: enum type, indicating how to enhance the picture.(eg OVISION_SUPER_RES)
*@param pic: picInfo struct, illustrating the format of the picture(RGB, NV12 etc.) and the height & width.
*@return return a pointer including the info of the interpreter and picture info.
*/
void* OVision_Init(int enhance_type,picInfo *pic);

/*
Process part, try to enhance the picture and fill in the output buffer.
Reminder, the format of NV12 for input and output would be preferred, and would work faster.
*@param hhandle: the output of Init part. You can use a void pointer to save it.
*@param input: the buffer of input. You should arrange the buffer and pass on the address.
*@param output: the buffer of output. You should arrange the buffer and pass on the address.
*@return return a code demonstraing whether the process succeeded or not. OVISION_ENHANCE_OK=0 is success.
*/
int OVision_Process(void *hhandle, uint8_t *input, uint8_t *output);

/*
deinit part, release the room.
*@param hhandle: the output of precess part. You can use a void pointer to save it.
no return.
*/
void OVision_Deinit(void *hhandle);

#endif