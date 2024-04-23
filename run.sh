#!/bin/bash

fileNames=("vid0.avi" "vid1.avi" "vid2.avi")

for name in ${fileNames[@]}; do
    ./Record $name
    echo "Recording complete: $name"
done

