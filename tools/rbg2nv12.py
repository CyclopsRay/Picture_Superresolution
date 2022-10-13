import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import os
path = "F:/FinalProject/project1/data"
files= os.listdir(path) 
s = []
for file in files: 
    if not os.path.isdir(file): 
        RGB = mpimg.imread(path+"/"+file)*255.0     # Read RGB input image, multiply by 255 (set RGB range to [0, 255]).
        R, G, B = RGB[:, :, 0], RGB[:, :, 1], RGB[:, :, 2]  # Split RGB to R, G and B numpy arrays.
        rows, cols = R.shape

        if do_use_bt709:

            Y =  0.18258588*R + 0.61423059*G + 0.06200706*B + 16.0
            U = -0.10064373*R - 0.33857195*G + 0.43921569*B + 128.0
            V =  0.43921569*R - 0.39894216*G - 0.04027352*B + 128.0
        else:

            Y =  0.25678824*R + 0.50412941*G + 0.09790588*B + 16.0
            U = -0.14822290*R - 0.29099279*G + 0.43921569*B + 128.0
            V =  0.43921569*R - 0.36778831*G - 0.07142737*B + 128.0

        shrunkU = (U[0: :2, 0::2] + U[1: :2, 0: :2] + U[0: :2, 1: :2] + U[1: :2, 1: :2]) * 0.25
        shrunkV = (V[0: :2, 0::2] + V[1: :2, 0: :2] + V[0: :2, 1: :2] + V[1: :2, 1: :2]) * 0.25

        UV = np.zeros((rows//2, cols))  # Use // for integer division.

        UV[:, 0 : :2] = shrunkU
        UV[:, 1 : :2] = shrunkV

        NV12 = np.vstack((Y, UV))

        NV12 = np.floor(NV12 + 0.5).astype('uint8')


        # Write NV12 array to binary file
        NV12.tofile(path+"/"+file+".bin")