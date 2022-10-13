import tensorflow as tf
 
in_path=r'F:\project1\models\model_8350_360p_v1.pb'
out_path=r'F:\project1\models\model_8350_360p_v1.tflite'
 
input_tensor_name=['input']
input_tensor_shape={'input':[1,1000,1000,1]}
 
class_tensor_name=['output_final']
 
convertr=tf.compat.v1.lite.TFLiteConverter.from_frozen_graph(in_path,input_arrays=input_tensor_name
                                                   ,output_arrays=class_tensor_name
                                                   ,input_shapes=input_tensor_shape)

tflite_model=convertr.convert()

with open(out_path,'wb') as f:
    f.write(tflite_model)