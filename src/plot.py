import matplotlib.pyplot as plt 
import numpy as np 

x = np.range(0, np.e, 0.01)
y1 = np.exp(-x)
y2 = np.log(x)

fig = plt.figure()

ax1 = fig.add_subplot(111)
ax1.plot(x, y1)
ax1.set_ylabel('Y value for exp(-x)')
ax1.set_title("double Y axis")

ax2 = ax1.twinx()
ax2.plot(x, y2)
ax2.set_xlim([0, np.e])
ax2.set_ylabel('Y value for ln(x)')
ax2.set_xlabel('same x for both exp(-x) and ln(x)')

plt.show()