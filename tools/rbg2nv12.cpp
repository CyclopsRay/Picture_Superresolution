#include<bits/stdc++.h>
using namespace std;
int rgbToY(int r, int g, int b) {
    return (((66 * r + 129 * g + 25 * b + 128) >> 8) + 16);
}

int rgbToU(int r, int g, int b) {

    return (((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128);
}

int rgbToV(int r, int g, int b) {
    return (((112 * r - 94 * g - 18 * b + 128) >> 8) + 128);
}
void rgba32ToBgr24(char *rgba32, char *bgr24, int rgbaLength) {
    int groupNum = rgbaLength / 4;
    for (int i = 0; i < groupNum; i++) {
        *(bgr24) = *(rgba32 + 2);
        *(bgr24 + 1) = *(rgba32 + 1);
        *(bgr24 + 2) = *rgba32;
        bgr24 += 3;
        rgba32 += 4;
    }
}
void bgr24ToNv21(char *bgr24, char *nv21, int width, int height) {
    int yIndex = 0;
    int uvIndex = width * height;
    int bgrIndex = 0;
    int nv21EndPos = width * height * 3 / 2 - 2;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int b = bgr24[bgrIndex++];
            int g = bgr24[bgrIndex++];
            int r = bgr24[bgrIndex++];
            int y = rgbToY(r, g, b);
            nv21[yIndex++] = static_cast<char>((y));
            if ((j & 1) == 0 && (bgrIndex & 0b100) == 0 && uvIndex < nv21EndPos) {
                int u = rgbToU(r, g, b);
                int v = rgbToV(r, g, b);
                nv21[uvIndex++] = static_cast<char>((v));
                nv21[uvIndex++] = static_cast<char>((u));
            }
        }
    }
}