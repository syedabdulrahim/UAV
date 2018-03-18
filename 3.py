import numpy as np
import cv2

img=cv2.imread('first.jpg',cv2.IMREAD_COLOR)
cv2.line(img,(0,0),(150,150),(0,0,15),15)
cv2.rectangle(img,(0,0),(150,155),(255,80,120),5)
cv2.circle(img,(150,155),30,(0,0,0),-1)
cv2.imshow('hi',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
