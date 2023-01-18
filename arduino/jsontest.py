import time
import json
import serial
from pprint import pprint
import random

forward = {
    "x": 0,
    "y": 1,
}

backward = {
    "x": 0,
    "y": -1,
}

left = {
    "x": -1,
    "y": 1,
}

right = {
    "x": 1,
    "y": 1,
}

if __name__ == "__main__":
    print ("Ready...")
    ser  = serial.Serial("/dev/ttyACM0", baudrate= 9600, 
           timeout=2.5, 
           parity=serial.PARITY_NONE, 
           bytesize=serial.EIGHTBITS, 
           stopbits=serial.STOPBITS_ONE
        )
    if ser.isOpen():
        for i in range(0, 10):
            print(json.dumps(forward).encode('ascii'))
            ser.write(json.dumps(forward).encode('ascii'))
            print('forward')
            time.sleep(1)
            ser.write(json.dumps(backward).encode('ascii'))
            print('backward')
            time.sleep(1)
            ser.write(json.dumps(left).encode('ascii'))
            print('left')
            time.sleep(1)
            ser.write(json.dumps(right).encode('ascii'))
            print('right')
            time.sleep(1)
        ser.write(json.dumps({"linear": {"x": 0, "y": 0}}).encode('ascii'))
        ser.close()
    else:
        print ("opening error")