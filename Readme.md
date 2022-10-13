# Picture enhance SDK for x86

This project is constructed by CMake.

CMake is recommanded to construct your project.

To run the code, you need to use your own model file, and transfer it into binary form.

To run the code, you need to download the tensorflow sdk and move it under the /include directory.

##### Tools required for SDK if you want to use shared object:

```shell
lib/lib_enhance.so
include/pic_enhance.h
```

and in CMakeLists.txt:

```cmake
target_link_libraries(target-project
    lib_enhance.so
    )
```

##### Tools required for SDK if you want to use static object:

```
lib/lib_enhance.a # This file is protected and isn't uploaded in the repository
lib/libtensorflow-lite.a
include/pic_enhance.h
```

and in CMakeLists.txt:

```cmake
target_link_libraries(target-project 
    lib_enhance.a # This file is protected and isn't uploaded in the repository
    libtensorflow-lite.a
    Threads::Threads
    dl
    )
```

For more details about APIs, see ```include/pic_enhance.h```

See how to compile in the ``example/example_nv12`` directory!

