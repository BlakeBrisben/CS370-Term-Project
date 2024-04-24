import cv2
import numpy as np
import socket
import sys
import pickle
import struct

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('10.0.0.36', 8083))

fileName = sys.argv[1]

file = open('vid/' + fileName, 'rb')
print(f'Sending: {fileName}')

data = file.read(4096)

while(data):
    clientsocket.send(data)
    data = file.read(4096)

file.close()
clientsocket.close()
