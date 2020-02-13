import numpy as np
import matplotlib.pyplot as plt

hr = np.loadtxt("hll1000000.list")
mr = np.loadtxt("mle1000000.list")
hr = hr[:100]
mr = mr[:100]

print(np.std(hr)/np.mean(hr)*100, np.mean(hr))
print(np.std(mr)/np.mean(mr)*100, np.mean(mr))