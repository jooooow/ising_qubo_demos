import numpy as np
import random
C = [2,4,6,3,1,7,4,3,6,4]
N = len(C)
Q = np.zeros([N,N])
for i in range(N):
    Q[i][i] = 4 * C[i] * (C[i] - sum(C))
    for j in range(i + 1,N):
        Q[i][j] = 8 * C[i] * C[j]
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
    print("---result---")
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
T = 1
spin = np.random.randint(0,2,N)
for s in range(S):
    for i in range(N):
        energy = GetEnergy(spin)
        spin[i] = 1 - spin[i]
        energy = GetEnergy(spin) - energy
        if energy <= 0:
            spin[i] = spin[i]
        elif random.random() <= np.exp(-energy / T):
            spin[i] = spin[i]
        else:
            spin[i] = 1 - spin[i]

'''for s in range(S):
    for i in range(N):
        temp_spin = 1 - spin[i]
        energy = temp_spin * Q[i][i]
        for j in range(i + 1, N):
            energy += temp_spin * Q[i][j] * spin[j]
        energy *= 2'''
        
GetResult(spin)
