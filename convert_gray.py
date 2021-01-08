import numpy as np
from scipy.misc import imread, imsave, imresize

img = imread('cat.jpg')

print img.shape
print img[:,:,0:0].shape
print img[:,:,0:1].shape
print img[:,:,0].shape

mean_R = np.mean(img[:,:,0])
std_R = np.std(img[:,:,0])

mean_G = np.mean(img[:,:,1])
std_G = np.std(img[:,:,1])

mean_B = np.mean(img[:,:,2])
std_B = np.std(img[:,:,2])

print (mean_R, mean_G, mean_B)
print (std_R, std_G, std_B)

gray_img = 0.2989*img[:,:,0] + 0.5870*img[:,:,1] + 0.1140*img[:,:,2]
imsave('cat_gray.jpg', gray_img) 
