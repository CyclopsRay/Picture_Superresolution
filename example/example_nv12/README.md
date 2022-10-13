#### This project is telling you how to use a NV12 format picture as input.

This project is using the shared library of ovision_enhance sdk.

There are 3 place you need to modify:

```cpp
FILE *fin
int in_w=;
int in_h=;
```

To see the picture, type:

```shell
ffplay -pixel_format nv12 -f rawvideo -video_size 1400x1400 ${PROJECT_SOURCE_PATH}/project1/example/example_nv12/out_final.bin	
```

where ${PROJECT_SOURCE_PATH} is the place you put project1