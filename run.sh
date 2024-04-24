#!/bin/bash

fileNames=("vid0.avi" "vid1.avi" "vid2.avi")

while true; do
    for name in ${fileNames[@]}; do
        ./Record $name
        python3 socket_client.py $name &
        echo "Recording complete: $name"
    done
done

