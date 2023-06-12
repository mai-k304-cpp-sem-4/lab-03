import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

file_name = 'Glases/цвет морской волны.png'
img = np.array(Image.open(file_name).convert('RGB'))
fig, ax = plt.subplots()
ax.imshow(img)
ax.set_title(file_name)
plt.show()

for i in range(0, img.shape[0]):
    for j in range(0, img.shape[1]):
        if (img[i][j][0] != 0) or (img[i][j][0] != 0) or (img[i][j][0] != 0):
          temp = "SetPixel(hdc, x + " + str(j) + ", y + " + str(i) + ", RGB(" + str(img[i][j][0]) + ", " + str(img[i][j][1]) + ", " + str(img[i][j][2]) + "));"
          print(temp)

for i in range(0, img.shape[0]):
    for j in range(0, img.shape[1]):
        if (img[i][j][0] != 0) or (img[i][j][0] != 0) or (img[i][j][0] != 0):
          temp = "SetPixel(hdc, x + " + str(j) + ", y + " + str(i) + ", RGB(12, 13, 13));"
          print(temp)