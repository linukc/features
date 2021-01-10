# y in ycc equal to grayscale
#Gaussian blur reduce noise
#Equalize improve quality

import cv2
import numpy as np

def hisEqulColor(img):
        ycrcb=cv2.cvtColor(img,cv2.COLOR_BGR2YCR_CB)
        channels=cv2.split(ycrcb)
        cv2.equalizeHist(channels[0],channels[0])
        cv2.merge(channels,ycrcb)
        cv2.cvtColor(ycrcb,cv2.COLOR_YCR_CB2BGR,img)
        return img

def auto_canny(image, sigma=0.33):
	# compute the median of the single channel pixel intensities
        if image.shape[-1] == 3:
            ycrcb = cv2.cvtColor(image,cv2.COLOR_BGR2YCR_CB)
            image = cv2.split(ycrcb)[0]
            print(image[250:260,350:360])
        v = np.median(image)
        # apply automatic Canny edge detection using the computed median
        lower = int(max(0, (1.0 - sigma) * v))
        upper = int(min(255, (1.0 + sigma) * v))
        #print(lower, upper)
        edged = cv2.Canny(image, lower, upper)
        # return the edged image
        return edged
    
image = cv2.imread('ntuWoUDpeSk.jpg')
auto_canny(image)
image = cv2.imread('ntuWoUDpeSk.jpg',0)
print(image[250:260,350:360])
#gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#blur = cv2.GaussianBlur(image, (5, 5), 0)
#dst = cv2.equalizeHist(blur)
#ret, otsu = cv2.threshold(dst,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
#print(ret)
#canny = cv2.Canny(dst, 0.5*ret, ret)
#cv2.imwrite('bl.jpg', canny)
#cv2.imshow('out', auto_canny(dst))
#cv2.imshow('out', canny)
