# Architect: Ryan J. Richards
# Obstacle Avoidance on RPI3
# OpenCV 3.2.0
# August. 2017


# Before running this code:
# open terminal and write: "source ~/.profile"
# then: "workon cv3"


from picamera.array import PiRGBArray
from picamera import PiCamera
import argparse
import time
import cv2
import numpy as np

# choose video to process from file
cap = cv2.VideoCapture("/media/pi/RYAN/Summer Research/SnowDrone/camera/videos/snowRun2.mp4")

#setup args
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=500, help="minimum area size")
args = vars(ap.parse_args())

#pause
time.sleep(0.1)

#setup coloring bounding arrays
lower_RGB = np.array([0,0,0])
upper_RGB = np.array([85,85,85])

# begin looping video and process frame-by-frame
while(1):
        # specify image as incoming frame from RPI camera
        ret,image = cap.read()

        # conduct color threshold
        mask = cv2.inRange(image,lower_RGB,upper_RGB)

        # find contours (similar to particle analysis)
       	(_,cnts, _) = cv2.findContours(mask, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
 
	# loop over the contours
	for c in cnts:
		# if the contour is too small, ignore it
		if cv2.contourArea(c) < args["min_area"]:
			continue
 
		# compute the bounding box for the contour, draw it on the frame,
		# and update the text
		(x, y, w, h) = cv2.boundingRect(c)
		cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2) 

        # show the images
        cv2.imshow("mask",mask)
        cv2.imshow("img",image)
        
        # termination by pressing 'esc' (escape key)
        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break
        elif k == ord('s'):
            cv2.imwrite('mask.png',mask)
            cv2.imwrite('image.png',image)

# terminate windows 
cv2.destroyAllWindows()
cap.release()
