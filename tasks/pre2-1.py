import numpy as np

v = np.array([[1], [0]])
theta = np.pi * 0.25 # e.g.
R = np.array([[np.cos(theta), np.sin(theta)],
              [-np.sin(theta), np.cos(theta)]])
vt = np.matmul(R, v)
print(vt)


# 逆时针旋转 $\theta$ 度. 这等价于在复平面乘上 $e^{i\theta}$.