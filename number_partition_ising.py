import numpy as np
import random

def GetEnergy(spin):
    e = 0
    for i in range(N):
        for j in range(i + 1, N):
            e += J[i][j] * spin[i] * spin[j]
        e += h[i][i] * spin[i]
    return e

def GetEnergy2(spin):
    sum = 0
    for i in range(N):
        sum += C[i] * spin[i]
    return sum**2

def GetResult(spin):
    print("------ result ------")
    print(spin)
    print("energy : %d" % GetEnergy(spin))
    print("energy2 : %d" % GetEnergy2(spin))
    sum1 = 0
    sum2 = 0
    for i in range(N):
        if spin[i] == 1:
            sum1 += C[i]
        elif spin[i] == -1:
            sum2 += C[i]
    print("sum1 : %d  sum2 : %d" % (sum1,sum2))

#C = [2,10,3,8,5,7,9,5,3,2]
C = np.random.randint(-11,11,100)
print(C)
N = len(C)
h = np.zeros([N,N])
J = np.zeros([N,N])
for i in range(N):
    for j in range(i + 1, N):
        J[i][j] = 2 * C[i] * C[j]
J = J + J.T * (1-np.eye(N))
print(J)

spin = np.random.randint(0,2,N) * 2 - 1
GetResult(spin)

S = 100
T = 2

for s in range(S):
    for i in range(N):
        temp = spin[i] * -1;
        e = h[i][i] * temp
        for j in range(N):
            e += temp * J[i][j] * spin[j]
        e *= 2
        if e <= 0:
            spin[i] *= -1
        elif random.random() <= np.exp(-e / T):
            spin[i] *= -1
  
GetResult(spin)



