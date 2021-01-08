import numpy as np
from scipy import misc
import matplotlib.pyplot as plt

def de_noise(img, filter_size, mode='mean'):
  height = img.shape[0]; width = img.shape[1]

  filter_half = filter_size//2
  de_noise_img = np.zeros_like(img)
  for i in range(filter_half, height - filter_half):
    for j in range(filter_half, width - filter_half):
      if mode=='mean':
        de_noise_img[i,j] = np.mean(img[i-filter_half:i+filter_half+1, j-filter_half:j+filter_half+1])
      elif mode=='median':
        de_noise_img[i,j] = np.median(img[i-filter_half:i+filter_half+1, j-filter_half:j+filter_half+1])

  error = np.mean(np.abs(img - de_noise_img)) * 255

  return de_noise_img, error

img = misc.imread('lena_gray.gif', mode='L') / 255.
noise = np.random.normal(loc=0.0, scale=0.2, size=img.shape)
noise_img = np.clip(img + noise, 0, 1)
de_noise_img1, error1 = de_noise(noise_img, 3, mode='mean')
de_noise_img2, error2 = de_noise(noise_img, 3, mode='median')
de_noise_img3, error3 = de_noise(noise_img, 5, mode='mean')
de_noise_img4, error4 = de_noise(noise_img, 5, mode='median')

misc.imsave('save/noise.png', noise_img)
misc.imsave('save/de_noise1.png', de_noise_img1)
misc.imsave('save/de_noise2.png', de_noise_img2)
misc.imsave('save/de_noise3.png', de_noise_img3)
misc.imsave('save/de_noise4.png', de_noise_img4)
print (error1, error2, error3, error4)