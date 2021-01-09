import cv2

def FLD(image):
    # Create default Fast Line Detector class
#_length_threshold=70
    fld = cv2.ximgproc.createFastLineDetector(_canny_aperture_size=7,
_length_threshold=50, _do_merge=True)
    # Get line vectors from the image
    lines = fld.detect(cv2.cvtColor(image, cv2.COLOR_BGR2GRAY))
    # Draw lines on the image
    line_on_image = fld.drawSegments(image, lines)
    # Plot
    return line_on_image

#full_name = 'ntuWoUDpeSk.jpeg'
#img = cv2.imread(full_name, cv2.IMREAD_COLOR)
#img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#cv2.imwrite('fld.jpg', FLD(img_gray))
cap = cv2.VideoCapture('WIN_20210103_20_39_07_Pro.mp4')

while(cap.isOpened()):
    ret, frame = cap.read()

    cv2.imshow('frame', FLD(frame))
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    cv2.waitKey(50)

cap.release()
cv2.destroyAllWindows()

