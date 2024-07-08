import numpy as np
import matplotlib.pyplot as plt

v1 = []
v0 = np.array([1, 0])
theta = np.linspace(0, 2 * np.pi, 6)
for tht in theta:
    R = np.array([[np.cos(tht), np.sin(tht)],
                 [-np.sin(tht), np.cos(tht)]])
    v1.append(R @ v0)
v1 = np.array(v1)

plt.quiver(0, 0, v0[0], v0[1], color='red', angles='xy', scale_units='xy', scale=1)
for i in range(len(v1)):
    plt.quiver(0, 0, v1[i, 0], v1[i, 1], 
               color='blue', angles='xy', scale_units='xy', scale=1)

plt.scatter(0, 0, color='black')
plt.xlim(-1.5, 1.5)
plt.ylim(-1.5, 1.5)
plt.gca().set_aspect('equal', adjustable='box')
plt.show()

# 逆时针旋转 $\theta$ 度. 这等价于在复平面乘上 $e^{i\theta}$.