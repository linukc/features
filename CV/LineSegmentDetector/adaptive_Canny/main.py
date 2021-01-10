# y in ycc equal to grayscale
#Gaussian blur reduce noise
#Equalize improve quality

import cv2
import numpy as np

def FLD(image, th1, th2):
    # Create default Fast Line Detector class
#_length_threshold=70
    fld = cv2.ximgproc.createFastLineDetector(_canny_aperture_size=5,
_length_threshold=50, _do_merge=True, _canny_th1=th1,_canny_th2=th2)
    # Get line vectors from the image
    lines = fld.detect(cv2.cvtColor(image, cv2.COLOR_BGR2GRAY))
    # Draw lines on the image
    line_on_image = fld.drawSegments(image, lines)
    # Plot
    return line_on_image

def hisEqualColor(img):
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
        v = np.median(image)
        # apply automatic Canny edge detection using the computed median
        lower = int(max(0, (1.0 - sigma) * v))
        upper = int(min(255, (1.0 + sigma) * v))
        edged = cv2.Canny(image, lower, upper)
        # return the edged image
        return edged
    
image = cv2.imread('doroga_razmetka_trassa_asfalt_119431_1920x1200.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
blur = cv2.GaussianBlur(gray, (5, 5), 0)
dst = cv2.equalizeHist(blur)
ret, otsu = cv2.threshold(dst,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)

image = cv2.imread('doroga_razmetka_trassa_asfalt_119431_1920x1200.jpg')
blur = cv2.GaussianBlur(image, (5, 5), 0)
dst = hisEqualColor(blur)
#print(ret)
#canny = cv2.Canny(dst, 0.5*ret, ret)
#cv2.imwrite('bl.jpg', canny)
#cv2.imshow('out', auto_canny(dst))
cv2.imwrite('out.jpg', FLD(dst, ret*0.5, ret))
