import numpy as np
import cv2

img=cv2.imread('first.jpg',1)
img[200:300,200:300]=[0,0,0]

img[0:100,0:100]=img[200:300,200:300]
cv2.imshow('h',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
