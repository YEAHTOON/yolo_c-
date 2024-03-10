import cv2
import sys
import numpy as np


cap = cv2.VideoCapture(0)


#获得输入
def getInput():

    # result = np.zeros((640,480,3))

    ret, frame = cap.read()

    return frame

