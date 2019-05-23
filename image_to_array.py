from PIL import Image



im = Image.open("/home/pi/python_games/cat.png")
im.show()

with open('picture.txt', 'w') as f:
    f.write("%s\n" % str(im.getdata().size))
    for pixel in iter(im.getdata()):
        f.write("%s\n" % str(pixel))

#for pixel in iter(im.getdata()):
#    print (pixel)
