import RPi.GPIO as GPIO
from time import sleep
import subprocess
import sys
import pygame.mixer

pygame.mixer.init()
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.OUT)
GPIO.setup(12, GPIO.OUT)
GPIO.output(11, False)
GPIO.output(12, False)

def detect():
    """Detects qr code from camera and returns string that represents that code.

    return -- qr code from image as string
    """
    playSound("Searching2")
    subprocess.call(["raspistill -n -t 500 -w 720 -h 720 -o cam.png"],shell=True)
    process = subprocess.Popen(["zbarimg -D cam.png"], stdout=subprocess.PIPE, shell=True)
    (out, err) = process.communicate()

    qr_code = None

    # out looks like "QR-code: Xuz213asdY" so you need
    # to remove first 8 characters plus whitespaces
    if len(out) > 8:
        qr_code = out[8:].strip()

    return qr_code

def searchQR():
    qrcode = None
    while qrcode == None:
         qrcode = detect()
    return qrcode

def playSound(soundFile):
    print("Playing sound")
    print("sounds/" + soundFile + ".aiff")
    sound = pygame.mixer.Sound("sounds/" + soundFile + ".aiff")
    sound.play()

def orange():
    GPIO.output(11, False)
    GPIO.output(12, True)

def blue():
    GPIO.output(11, True)
    GPIO.output(12, False)

def rainbowColours():
    GPIO.output(11, True)
    GPIO.output(12, True)

def ledsOff():
    GPIO.output(11, False)
    GPIO.output(12, False)
    
def menu():
    print("Enter value")
    print("1 for orange, 2 for blue, 3 for rainbow, 4 for no LEDs, 5 for QRcode, 9 for quit")
    thing = str(raw_input())
    if thing == "1":
        orange()
    elif thing == "2":
        blue()
    elif thing == "3":
        rainbowColours()
    elif thing == "5":
        book = searchQR()
        print("Book found!")
        print("----------------")
        print("")
        print(book)
        print("")
        print("----------------")
    elif thing == "4":
        ledsOff()
    elif thing == "9":
        GPIO.cleanup()
        sys.exit()
    else:
        print("Unknown entry")

while True:
    menu()
