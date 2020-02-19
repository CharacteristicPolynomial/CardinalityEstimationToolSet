import numpy as np
import matplotlib.pyplot as plt

hr = np.loadtxt("hll800000.list")
mr = np.loadtxt("mse800000.list")
mwr = np.loadtxt("msew800000.list")

num_bins = 500

plt.figure()
plt.hist(hr, num_bins, facecolor='red', alpha=0.3)
plt.show()
plt.hist(mr, num_bins, facecolor='green', alpha=0.3)
plt.show()
plt.hist(mwr, num_bins, facecolor='blue', alpha=0.3)
plt.show()