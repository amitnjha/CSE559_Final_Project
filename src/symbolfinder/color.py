
import cv2
import numpy as np

def noOp(x):
  pass

cap = cv2.VideoCapture(0)
lowH = 55
highH = 140

lowS = 11
highS = 67

lowV = 185
highV = 243

if(not cap.isOpened()):
  print("Cannot open camera")
else:
  if(not cap.isOpened()):
    print("Cannot open camera")
  else:
    cap.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, 320)
    cap.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, 240)

    cv2.namedWindow("Control")
        
    cv2.createTrackbar("Low Hue", "Control", lowH, 179, noOp)
    cv2.createTrackbar("High Hue", "Control", highH, 179, noOp)

    cv2.createTrackbar("Low Sat", "Control", lowS, 255, noOp)
    cv2.createTrackbar("High Sat", "Control", highS, 255, noOp)

    cv2.createTrackbar("Low Value", "Control", lowV, 255, noOp)
    cv2.createTrackbar("High Value", "Control", highV, 255, noOp)

    spotFilter = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
    maskMorph = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (10, 10))
    
    while(1):
      frameCount = 0
      while frameCount < 5:
        cap.read()
        frameCount = frameCount + 1
      success, frame = cap.read()
      frame = cv2.imread('c:/Users/amitjha/Documents/Washu/CSE559a/spring_2015/projects/PackageProject_Final/images/straight_bg.jpg')
      if (not success):
        print("Cannot read a frame from the camera")
      else:
        lowH = cv2.getTrackbarPos("Low Hue", "Control")
        highH = cv2.getTrackbarPos("High Hue", "Control")
        lowS = cv2.getTrackbarPos("Low Sat", "Control")
        highS = cv2.getTrackbarPos("High Sat", "Control")
        lowV = cv2.getTrackbarPos("Low Value", "Control")
        highV = cv2.getTrackbarPos("High Value", "Control")

        imgHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        imgThresholded = cv2.inRange(imgHSV, np.array([lowH, lowS, lowV]), np.array([highH, highS, highV]))

        cv2.imshow("Ranged Image", imgThresholded)

        # Remove spots in image 
        imgThresholded = cv2.erode(imgThresholded, spotFilter)
        # Create mask
        imgThresholded = cv2.dilate(imgThresholded, maskMorph)
        
        cv2.imshow("Thresholded", imgThresholded)
        cv2.imshow("Original", frame)
        
      if (cv2.waitKey(1) == 27):
        break
    cap.release()

    # Print out the final settings ready to copy
    # and paste into tracking script
    
    print("  lowH = " + str(lowH))
    print("  highH = " + str(highH))
    print("")
    print("  lowS = "  + str(lowS))
    print("  highS = "  + str(highS))
    print("")
    print("  lowV = " + str(lowV))
    print("  highV = " + str(highV))

cv2.destroyAllWindows()