from datetime import datetime
import socket
import sys
import cv2
import pickle
import numpy as np
import struct


HOST = '127.0.0.1'
PORT = 8083

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')

s.bind((HOST, PORT))
print('Socket bind complete')
s.listen(10)
print('Socket now listening')

now = datetime.now()
fileName = 'vid' + now.strftime('%m%d%H:%M')

file = open(fileName, 'w')


data = b''
payload_size = struct.calcsize("L")

while True:
    conn, addr = s.accept()
    data = conn.recv(4096)
    
    while(data):
        file.write(data)
        data = conn.recv(4096)

    file.close()
    conn.close()
     
