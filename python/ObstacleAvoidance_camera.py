# Architect: Ryan J. Richards
# Obstacle Avoidance on RPI3
# OpenCV 3.2.0
# August. 2017


# Before running this code:
# open terminal and write: "source ~/.profile"
# then: "workon cv3"

import argparse
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np

ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=500, help="minimum area size")
args = vars(ap.parse_args())

#specify camera as the attached RPI camera
camera = PiCamera()

#specify resolution and framerate
camera.resolution = (640,480)
camera.framerate = 32

#initialize capture
rawCapture = PiRGBArray(camera, size=(640,480))

#pause
time.sleep(0.1)

#setup bounding color arrays
lower_RGB = np.array([0,0,0])
upper_RGB = np.array([85,85,85])

#begin looping for camera capture and LPT
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        #specify image as incoming frame from RPI camera
        image = frame.array

        #conduct color threshold
        mask = cv2.inRange(image,lower_RGB,upper_RGB)

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

        #show the images
        cv2.imshow("mask",mask)
        cv2.imshow("img",image)
        
        #termination by pressing 'q'
        key = cv2.waitKey(1) & 0xFF
        rawCapture.truncate(0)
        if key == ord("q"):
            break
        elif key == ord("s"):
            cv2.imwrite('mask.png',mask)
            cv2.imwrite('image.png',image)

# terminate windows 
cv2.destroyAllWindows()
cap.release()
