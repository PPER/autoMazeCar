import time, sensor, image
from image import SEARCH_EX, SEARCH_DS
from pyb import UART


sensor.reset()

sensor.set_contrast(1)
sensor.set_gainceiling(16)

sensor.set_framesize(sensor.QQVGA)
sensor.set_pixformat(sensor.GRAYSCALE)

template1 = image.Image("LorR1left.pgm")
template2 = image.Image("LorR2right.pgm")#camera rotate 90 degrees clockwise


uart = UART(3, 9600)

clock = time.clock()


#Run template matching
while (True):
    clock.tick()

    inp = 1
    #inp = uart.read()

    if inp:

        img = sensor.snapshot()

        left = img.find_template(template1, 0.70, step=2, search=SEARCH_EX)
        right = img.find_template(template2, 0.70, step=2, search=SEARCH_EX)


        if left:
            img.draw_rectangle(left)
            uart.write('1')
            print("left")
            time.sleep(10000)  #wait for 5 seconds before the next matching


        elif right:
            img.draw_rectangle(right)
            uart.write('2')
            print("right")
            time.sleep(10000)

        else:
            uart.write('0')
            print("not found")

    print(clock.fps())

