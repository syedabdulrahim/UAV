import cv2
import numpy as np


img1=cv2.imread('one.jpg')
img2=cv2.imread('four.jpg')

#add=img1+img2
#weighted=cv2.addWeighted(img1,0.2,img2,0.8,0)
#  cv2.imshow('add',weighted)
rows,cols,channel=img2.shape

#print(rows,cols,channel)

roi=img2[0:rows,0:cols]
img2gray=cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
ret,mask=cv2.threshold(img2gray,220,255,cv2.THRESH_BINARY_INV)
#cv2.imshow('h',mask)
mask_inv=cv2.bitwise_not(mask)
img1_bg=cv2.bitwise_and(roi,roi,mask=mask_inv)
img2_fg=cv2.bitwise_and(img2,img2,mask=mask_inv)
dst=cv2.add(img1_bg,img2_fg)
img1[0:rows,0:cols]=dst

cv2.imshow('h',img1_bg)
cv2.imshow('h4',img2_fg)
cv2.waitKey(0)
cv2.destroyAllWindows()
