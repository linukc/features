import cv2
import numpy as np
import os
from pylsd import lsd

#full_name = 'ntuWoUDpeSk.jpeg'
#img = cv2.imread(full_name, cv2.IMREAD_COLOR)
#img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

#segments = lsd(img_gray, scale=0.8, sigma_scale=0.9, ang_th=22.5, quant=2.0, eps=150, density_th=0.7, n_bins=1024, max_grad=255.0)

#for i in range(segments.shape[0]):
#    pt1 = (int(segments[i, 0]), int(segments[i, 1]))
#    pt2 = (int(segments[i, 2]), int(segments[i, 3]))
#    width = segments[i, 4]
#    cv2.line(img, pt1, pt2, (0, 0, 255), int(np.ceil(width)))

#cv2.imwrite('output.jpg', img)

cap = cv2.VideoCapture('WIN_20210103_20_39_07_Pro.mp4')

while(cap.isOpened()):
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#, scale=0.8, sigma_scale=0.9, ang_th=22.5, quant=2.0, eps=150, density_th=0.7, n_bins=1024, max_grad=255.0
    segments = lsd(gray)

    for i in range(segments.shape[0]):
        pt1 = (int(segments[i, 0]), int(segments[i, 1]))
        pt2 = (int(segments[i, 2]), int(segments[i, 3]))
        width = segments[i, 4]
        cv2.line(frame, pt1, pt2, (0, 0, 255), int(np.ceil(width)))

    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

