#include"pic_enhance.h"

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <mutex>
using namespace std;
#define CLAP(a) (max((min(a, 0xff)), 0x00)) 
#undef clamp_g
#define clamp_g(x, minValue, maxValue) ((x) < (minValue) ? (minValue) : ((x) > (maxValue) ? (maxValue) : (x)))


unsigned char Clap(float x){
    if(x>255)return 255;
    if(x<0)return 0;
    return (unsigned char)x;
}    


void BGR2NV12( unsigned char *imgSrc, unsigned char *imgDst, int width, int height ){
    int w, h;
	int shift = 14, offset1 = 8192, offset2 = 2105344;
	int C0 = 1868, C1 = 9617, C2 = 4899, C3 = 11682, C4 = 9241;
 
	int r1,r2,g1,g2,b1,b2;
	
	unsigned char * pRGB1 = imgSrc;
	unsigned char * pRGB2 = imgSrc+width*3;
 
	unsigned char * pDY1 = imgDst;
	unsigned char * pDY2 = imgDst+width;
	unsigned char * pDUV = imgDst+width*height;
 
	for ( h = 0; h < height; h += 2 )
	{
		for ( w = 0; w < width; w += 2 )
		{
			b1 = *pRGB1++;
			g1 = *pRGB1++;
			r1 = *pRGB1++;
			*pDY1  = (b1 * C0 + g1 * C1 + r1 * C2 + offset1) >> shift;
			*pDUV++ = ((b1 - *pDY1) * C4 + offset2) >> shift;
			*pDUV++ = ((r1 - *pDY1) * C3 + offset2) >> shift;
			//*pDUV++ = ((b1 - *pDY1) * C4 + offset2) >> shift;
			pDY1++;
 
			b1 = *pRGB1++;
			g1 = *pRGB1++;
			r1 = *pRGB1++;
			*pDY1  = (b1 * C0 + g1 * C1 + r1 * C2 + offset1) >> shift;
			pDY1++;
 
			b2 = *pRGB2++;
			g2 = *pRGB2++;
			r2 = *pRGB2++;
			*pDY2  = (b2 * C0 + g2 * C1 + r2 * C2 + offset1) >> shift;
			pDY2++;
 
			b2 = *pRGB2++;
			g2 = *pRGB2++;
			r2 = *pRGB2++;
			*pDY2  = (b2 * C0 + g2 * C1 + r2 * C2 + offset1) >> shift;
			pDY2++;
		}
		pRGB1 += 3*width;
		pRGB2 += 3*width;
		pDY1 += width;
		pDY2 += width;
 
	}
}
void NV122BGR( unsigned char *imgY, unsigned char *imgDst,int width, int height ){
    int w, h;
	int shift = 14, offset = 8192;
	int C0 = 22987, C1 = -11698, C2 = -5636, C3 = 29049;
 
	int y1,y2,u1,v1;
 
	unsigned char * pY1 = imgY;
	unsigned char * pY2 = imgY+width;
	unsigned char * pUV = imgY+width*height;
	
	unsigned char * pD1 = imgDst;
	unsigned char * pD2 = imgDst+width*3;
 
	for ( h = 0; h < height; h +=2 )
	{
		for ( w = 0; w < width; w +=2 )
		{
			u1 = *pUV-128;
			pUV++;
			v1 = *pUV-128;
			pUV++;
 
			
			y1 = *pY1;
			y2 = *pY2;
 
			*pD1++ = CLAP(y1+((u1 * C3 + offset) >> shift));
			*pD1++ = CLAP(y1+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD1++ = CLAP(y1+((v1 * C0 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C3 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD2++ = CLAP(y2+((v1 * C0 + offset) >> shift));
 
			pY1++;
			pY2++;
			y1 = *pY1;
			y2 = *pY2;
 
			*pD1++ = CLAP(y1+((u1 * C3 + offset) >> shift));
			*pD1++ = CLAP(y1+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD1++ = CLAP(y1+((v1 * C0 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C3 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD2++ = CLAP(y2+((v1 * C0 + offset) >> shift));
			pY1++;
			pY2++;
 
		}
		pY1 += width;
		pY2 += width;
		pD1 += 3*width;
		pD2 += 3*width;
 
	}
}
int NV12Linear(unsigned char * srcImage, unsigned char * destImage, int srcW, int srcH, int destW, int destH){
    float timeX = 0.0f;
    float timeY = 0.0f;

    timeX = srcW * 1.0f / destW;
    timeY = srcH * 1.0f / destH;

    int i = 0;
    int j = 0;
    int k = 0;

    unsigned char * srcUV = srcImage + srcW * srcH;
    unsigned char * destUV = destImage + destW * destH;

    for (i = 0; i < destH; i++)
    {
        for (j = 0; j < destW; j++)
        {
            int srcIdX = 0;
            int srcIdY = 0;
            float srcfIdX = 0.0f;
            float srcfIdY = 0.0f;
            float weightX[2] = { 0.0f, 0.0f };
            float weightY[2] = { 0.0f, 0.0f };
            srcfIdX = j * timeX;
            srcfIdY = i * timeY;
            srcIdX = (int)(srcfIdX);
            srcIdY = (int)(srcfIdY);
            weightX[1] = srcfIdX - srcIdX;
            weightX[0] = 1.0f - weightX[1];
            weightY[1] = srcfIdY - srcIdY;
            weightY[0] = 1.0f - weightY[1];
            // destImage[(i * destW + j)] = (srcImage[(srcIdY * srcW + srcIdX)] * weightX[0] + srcImage[(srcIdY * srcW + clamp_g(srcIdX + 1, 0, srcW - 1))] * weightX[1]) * weightY[0] +
            //     (srcImage[(clamp_g(srcIdY + 1, 0, srcH - 1) * srcW + srcIdX)] * weightX[0] + srcImage[(clamp_g(srcIdY + 1, 0, srcH - 1) * srcW + clamp_g(srcIdX + 1, 0, srcW - 1))] * weightX[1]) * weightY[1];
            if (0 == i % 2 && 0 == j % 2)
            {
                int srcVUW = srcW / 2;
                int srcVUH = srcH / 2;
                int destVUy = i / 2;
                int destVUx = j / 2;
                int UVsrcIdX = 0;
                int UVsrcIdY = 0;
                float UVsrcfIdX = 0.0f;
                float UVsrcfIdY = 0.0f;
                float UVweightX[2] = { 0.0f };
                float UVweightY[2] = { 0.0f };
                UVsrcfIdX = destVUx * timeX;
                UVsrcfIdY = destVUy * timeY;
                UVsrcIdX = (int)(UVsrcfIdX);
                UVsrcIdY = (int)(UVsrcfIdY);
                UVweightX[1] = UVsrcfIdX - UVsrcIdX;
                UVweightX[0] = 1.0f - UVweightX[1];
                UVweightY[1] = UVsrcfIdY - UVsrcIdY;
                UVweightY[0] = 1.0f - UVweightY[1];
                destUV[(i / 2 * (destW / 2) + j / 2) * 2 + 0] =
                    (srcUV[(UVsrcIdY * srcVUW + UVsrcIdX) * 2 + 0] * weightX[0] + srcUV[(UVsrcIdY * srcVUW + clamp_g(UVsrcIdX + 1, 0, srcVUW - 1)) * 2 + 0] * weightX[1]) * weightY[0] +
                    (srcUV[(clamp_g(UVsrcIdY + 1, 0, srcVUH - 1) * srcVUW + UVsrcIdX) * 2 + 0] * weightX[0] + srcUV[(clamp_g(UVsrcIdY + 1, 0, srcVUH - 1) * srcVUW + clamp_g(UVsrcIdX + 1, 0, srcVUW - 1)) * 2 + 0] * weightX[1]) * weightY[1];
                destUV[(i / 2 * (destW / 2) + j / 2) * 2 + 1] =
                    (srcUV[(UVsrcIdY * srcVUW + UVsrcIdX) * 2 + 1] * weightX[0] + srcUV[(UVsrcIdY * srcVUW + clamp_g(UVsrcIdX + 1, 0, srcVUW - 1)) * 2 + 1] * weightX[1]) * weightY[0] +
                    (srcUV[(clamp_g(UVsrcIdY + 1, 0, srcVUH - 1) * srcVUW + UVsrcIdX) * 2 + 1] * weightX[0] + srcUV[(clamp_g(UVsrcIdY + 1, 0, srcVUH - 1) * srcVUW + clamp_g(UVsrcIdX + 1, 0, srcVUW - 1)) * 2 + 1] * weightX[1]) * weightY[1];


            }

        }
    }
    return 0;
}
