# OVision picture enhance SDK for x86

This project is constructed by CMake.

CMake is recommanded to construct your project.

##### Tools required for SDK if you want to use shared object:

```shell
lib/libovision_enhance.so
include/pic_enhance.h
```

and in CMakeLists.txt:

```cmake
target_link_libraries(target-project
    libovision_enhance.so
    )
```

##### Tools required for SDK if you want to use static object:

```
lib/libovision_enhance.a
lib/libtensorflow-lite.a
include/pic_enhance.h
```

and in CMakeLists.txt:

```cmake
target_link_libraries(target-project 
    libovision_enhance.a
    libtensorflow-lite.a
    Threads::Threads
    dl
    )
```

For more details about APIs, see ```include/pic_enhance.h```

See how to compile in the ``example/example_nv12`` directory!



##### version 0.1: Only support NV12 image as input, NV12 file as output. Only support x2 super resolution method.

In the ``example/example_rgb`` project, the code is demonstrated to use a jpeg picture as input, but OpenCV is required.

2021.8.18

##### version 0.2: Update the new example, simplify the code, remove the annotation

In the ``example/example_nv12`` project, the minimum code is demonstrated to use thenv12 binary file as input&output.

2021.8.19

##### version 0.3: Now the project support RGB as input.

Check the ``example/example_rgb`` project for more details.

2021.8.19