import numpy as np
import matplotlib.patches as pat
import matplotlib.pyplot as plt
import random

m = 64
q = 2
h = 7
cap = 100


n = 400000
for k in range(1000):
    plt.cla()
    board = np.zeros([cap, m])
    top = 0
    for _ in range(n):
        idx = random.randrange(m)
        temp = 0
        while random.randrange(2) > 0:
            temp+=1
        top = max(top,temp)
        board[temp, idx] = 1

    plt.plot([0, m], [top-h+0.5,top-h+0.5], color='red', linewidth=1)
    nboard = np.zeros([cap,m])
    for i in range(cap):
        temp = 0
        for j in range(m):
            if board[i,j] > 0:
                nboard[i,temp] = 1
                temp += 1
    board = nboard
    for i in range(cap):
        for j in range(m):
            if board[i,j] >0:
                rec = pat.Rectangle((j+1, i-0.5),0.8,0.8,alpha=0.5)
                plt.gca().add_patch(rec)
    for j in range(m):
        temp = 0
        for i in range(cap):
            if board[i,j] >0:
                temp = i
        rec = pat.Rectangle((j+1, temp-0.5),0.8,0.8,color='orange')
        plt.gca().add_patch(rec)
    plt.xlim(0,m+2)
    plt.ylim(0,40)
    plt.savefig("sortgridvis/fig"+str(k)+".png")