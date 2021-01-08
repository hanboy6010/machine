import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import imread, imsave, imresize

N = 100
M = 10000

img = imread('1.jpg')
gray_img = np.mean(img, axis=2)
gray_img = (gray_img - np.mean(gray_img)) / np.std(gray_img)
height = gray_img.shape[0]
width = gray_img.shape[1]

samples = []
for _ in range(M):
  hi = np.random.randint(low=0, high=height-1, size=N)
  wi = np.random.randint(low=0, high=width-1, size=N)
  samples.append(np.mean(gray_img[hi, wi]))

plt.hist(samples, 1000)
plt.show()