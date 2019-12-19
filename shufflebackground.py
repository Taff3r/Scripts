import os
import random 

BASE_DIR = "/home/simont/"
WP_DIR = "Pictures/Wallpapers"

def mapDir(dirName):
    imageMap = dict() 
    images = os.listdir(dirName)

    for i, img in enumerate(images):
        imageMap[i] = img

    return imageMap

dirName = os.path.join(BASE_DIR, WP_DIR)
imageMap = mapDir(dirName)
rand = random.randint(0, len(imageMap.keys()) - 1)

os.system("feh --bg-fill " + os.path.join(BASE_DIR, WP_DIR, imageMap[rand]))
