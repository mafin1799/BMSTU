import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt


def F(s, t, b, c):
    dudt = s[1]
    dvdt = -b * s[1] - c * np.sin(s[0])
    return [dudt, dvdt]


b = 0.25
c = 5.0
y0 = [0.0, np.pi - 0.1]
t = np.linspace(0, 10,50)
sol = odeint(F, y0, t, args=(b, c))
plt.plot(t, sol[:, 0], 'r')
plt.xlabel('t')
plt.ylabel('u(t)')
plt.grid()
plt.show()
