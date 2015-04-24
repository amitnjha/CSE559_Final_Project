import cv2

for i in range(20):
    print 'hello'

d = cv2.imread('c:/Users/amitjha/Documents/Washu/CSE559a/spring_2015/projects/PackageProject_Final/images/left.jpg')

cv2.imshow('hello',d)
cv2.waitKey(27000)

