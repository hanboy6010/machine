import numpy as np

def exp_dist_cdf_inv(u, lmd):
   return -np.log(1-u) / lmd # inverse funcion of exp dist CDF

num_samples = 10000
lmd = 1.0 / 20.0 # exp dist param: lambda

# sample from exp dist using numpy
x1 = np.random.exponential(scale=1.0/lmd, size=num_samples)

# sample from uniform dist using numpy
u = np.random.uniform(low=0.0, high=1.0, size=num_samples)
# transform uniform to exp dist using inverse CDF function
x2 = exp_dist_cdf_inv(u, lmd)

# plot
import matplotlib.pyplot as plt

plt.hist(x=x1, bins=range(150), histtype='step', color='red')
plt.hist(x=x2, bins=range(150), histtype='step', color='blue')

plt.show()