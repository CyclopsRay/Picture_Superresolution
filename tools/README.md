Remember to modify the dir in the .py file.

To transfer the tflite file to the binary header,

type:

```
xxd -i model.tflite > model.h
```

The rbg2nv12.py file works on a dir to transfer all the picture from RBG format to NV12 format ended with .bin.