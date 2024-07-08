import tensorcircuit as tc
from tensorcircuit.cloud import apis
import matplotlib.pyplot as plt
apis.set_provider("local")

# 调用本地code进行电路模拟
c = tc.Circuit(1)
c.H(0)
c.rz(0, theta=0)
U = c.matrix() # 量子门电路对应的矩阵
states = c.state() # 输出量子态
t = apis.submit_task(circuit=c, device="testing", shots=1024)
data = t.results(blocked=True) #产生0，1态的结果分布
print('data:', data)
detail = t.details() # 产生详细的参数信息
print("detail info:", t.details())

c.draw(output='mpl')
plt.show()
counts = t.results()
tc.results.counts.plot_histogram(counts) #柱状结果分布
plt.show()