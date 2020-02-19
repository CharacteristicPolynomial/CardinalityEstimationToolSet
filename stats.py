import numpy as np
import matplotlib.pyplot as plt

hr = np.loadtxt("hll800000.list")
mr = np.loadtxt("mse800000.list")
mwr = np.loadtxt("msew800000.list")
# hr = hr[:100]
# mr = mr[:100]

print(np.std(hr)/np.mean(hr)*100, np.mean(hr))
print(np.std(mr)/np.mean(mr)*100, np.mean(mr))
print(np.std(mwr)/np.mean(mwr)*100, np.mean(mwr))
n = 800000
hr -= n
mr -= n
mwr -= n
print(np.sum(np.square(hr))/n/n,np.sum(np.square(mr))/n/n
    ,np.sum(np.square(mwr))/n/n)