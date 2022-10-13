#include"pic_enhance.h"
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

using namespace std;
using namespace cv;

#define CLAP(a) (MAX((MIN(a, 0xff)), 0x00)) 

int main(){
    FILE *fp=fopen("../out_final.bin","wb");
    FILE *f=fopen("../out_nv.bin","wb");
    Mat img=imread("../test.jpg");
    int in_h=img.rows;
    int in_w=img.cols;
    picInfo *pI=new picInfo(OVISION_RGB,in_h,in_w);
    void* handle=OVision_Init(OVISION_SUPER_RES,pI);

    int out_h=pI->h;
    int out_w=pI->w;
        cout<<"params of in&out are "<<in_h<<" "<<in_w<<" "<<out_h<<" "<<out_w<<endl;
    //uint8_t *in_nv12=(uint8_t *)malloc(in_h*in_w*1.5);
    //uint8_t *out_model=(uint8_t *)malloc(out_h*out_w*1.5);
    uint8_t *out=(uint8_t *)malloc(out_h*out_w*3);
    //BGR2NV12(img.data,in_nv12,in_w,in_h);
    //    fwrite(in_nv12,sizeof(uint8_t),in_h*in_w*1.5,f);

    int flg=OVision_Process(handle,img.data,out);
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
    //NV122BGR(out_model,out,out_w,out_h);
    fwrite(out,sizeof(uint8_t),out_h*out_w*3,fp);
    OVision_Deinit(handle);
	Mat rgbimg(out_h,out_w,CV_8UC3);
	memcpy(rgbimg.data,out,out_w*out_h*3);
	imshow("Test",rgbimg);
	while(1)if(waitKey(100)==27)break;
    delete pI;
}