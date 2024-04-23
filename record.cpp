#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

int record(string fileName) {
    Mat image;

    VideoCapture cap(0);
    VideoWriter output;

    if(!cap.isOpened()) {
        return 1;
    } 

    int frameWidth = static_cast<int>(cap.get(3));
    int frameHeight = static_cast<int>(cap.get(4));
    int fps = cap.get(5);

    Size frameSize(frameWidth, frameHeight);
    
    output.open("vid/" + fileName, VideoWriter::fourcc('M', 'P', '4', '2'), cap.get(5), frameSize);
    if(!output.isOpened()) {
        return 2;
    }

    for(int i = 0; i < fps * 10; i++) {
        cap >> image;

        output << image;

        if(i % fps == 0) {
            cout << "Time elapsed(" << fileName << "): " << i / fps << endl;
        }

    }

    cap.release();
    output.release();

    return 0;
}

int main(int argc, char* argv[]) {

    if(argc != 2) {
        cout << "File name needs to be specified. Usage: \n\t./Record <filename.extension>\n";
        return EXIT_FAILURE;
    }

    string fileName = argv[1];
    int ret = record(fileName);
    if(ret == 1) {
        cout << "Camera was not opened successfully\n";
        return EXIT_FAILURE;
    } else if(ret == 2) {
        cout << "Output file was unable to be opened: " << fileName << endl;
        return EXIT_FAILURE;
    }

    return 0;
}
