import numpy as np
import random
#C = np.random.randint(1,11,100)
C = [2,4,6]
print(C)
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
    print("--------- result ---------")
    print(spin)
    print("energy : %d" % GetEnergy(spin))
    print("energy2 : %d" % GetEnergy2(spin))
    c1 = []
    c2 = []
    for i in range(N):
        if spin[i] == 0:
            c1.append(C[i])
        elif spin[i] == 1:
            c2.append(C[i])
    print(c1)
    print(c2)
    print("sum1 : %d  sum2 : %d" % (sum(c1),sum(c2)))
    print("--------------------------")

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
