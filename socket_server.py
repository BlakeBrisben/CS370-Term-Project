from datetime import datetime
import socket
import sys
import cv2
import pickle
import numpy as np
import struct


HOST = '10.0.0.36'
PORT = 8083

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')

s.bind((HOST, PORT))
print('Socket bind complete')
s.listen(10)
print('Socket now listening')


while (True):
    conn, addr = s.accept()

    now = datetime.now()
    fileName = 'invid\\vid' + now.strftime('%m%d%H%M%S') + '.avi'
    print(fileName)

    file = open(fileName, 'wb')
    print('file open')
    
    if(file):
        data = b''
        payload_size = struct.calcsize("L")

        data = conn.recv(4096)
        print('receiving')
        
        while(data):
            file.write(data)
            data = conn.recv(4096)

        print(f'finished writing {fileName}')
        file.close()
        conn.close()
     
