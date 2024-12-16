import cv2
import time

def getPath():
    path = ""
    inifile = ""
    with open("./savePath.ini", "r") as f:
        inifile = f.read()
        f.close()
    path = inifile.split(" ")[2]
    return path

def bmp2png():
    savePath = getPath()
    bmp_image = cv2.imread("./temp.bmp")

    if bmp_image is None:
        print("failed to load bmp file")
    else:
        cv2.imwrite(savePath + str(int(time.time())) + ".png", bmp_image)

# print(getPath())
# if __name__ == "__name__":
#     bmp2png()
    
