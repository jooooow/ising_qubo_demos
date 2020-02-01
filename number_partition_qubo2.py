import numpy as np
import random
C = [2,4,6,3,1,7,4,2,3,8,7,5,6,7,8,2,3,4,11,9]
N = len(C)
Q = np.zeros([N,N])
for i in range(N):
    Q[i][i] = 4 * C[i] * (C[i] - sum(C))
    for j in range(i + 1,N):
        Q[i][j] = 8 * C[i] * C[j]
Q = Q + Q.T * (1-np.eye(N))
print(Q)

def GetEnergy(spin):
    e = 0
    for i in range(N):
        for j in range(i, N):
            e += Q[i][j] * spin[i] * spin[j]
    return e

def GetEnergy2(spin):
    e = 0
    for i in range(N):
        e += C[i] * spin[i]
    for i in range(N):
        e -= C[i] * (1 - spin[i])
    return e ** 2

def GetResult(spin):
    print("------ result ------")
    print(spin)
    print("energy : %d" % GetEnergy(spin))
    print("energy2 : %d" % GetEnergy2(spin))
    sum1 = 0
    sum2 = 0
    for i in range(N):
        if spin[i] == 0:
            sum1 += C[i]
        elif spin[i] == 1:
            sum2 += C[i]
    print("sum1 : %d  sum2 : %d" % (sum1,sum2))

S = 100
T = 0.1
spin = np.random.randint(0,2,N)
GetResult(spin)

for s in range(S):
    for i in range(N):
        temp_spin = 1 if spin[i] == 0 else -1
        energy = temp_spin * Q[i][i]
        for j in range(N):
            if j == i:
                continue
            energy += temp_spin * Q[i][j] * spin[j]
        if energy <= 0:
            spin[i] = 1 - spin[i]
        elif random.random() <= np.exp(-energy / T):
            spin[i] = 1 - spin[i]

GetResult(spin)
