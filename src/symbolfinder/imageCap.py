import cv2

cap = cv2.VideoCapture(0)
 
    
while True:
    sucess, frame =  cap.read()
    cv2.imshow("hello",frame);
    cv2.waitKey(27)
    cv2.line( (0,0),(25,25),(25,25),(25,25))
    #cv2.drawKeypoints(frame)