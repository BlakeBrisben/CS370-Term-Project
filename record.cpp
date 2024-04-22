#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

int main() {
    Mat image;

    namedWindow("Display");

    VideoCapture cap(0);
    VideoWriter output;

    if(!cap.isOpened()) {
        cout << "unable to open camera" << endl;
        return 1;
    } 

    int frameWidth = static_cast<int>(cap.get(3));
    int frameHeight = static_cast<int>(cap.get(4));

    Size frameSize(frameWidth, frameHeight);
    
    output.open("vid/test.avi", VideoWriter::fourcc('M', 'P', '4', '2'), cap.get(5), frameSize);
    if(output.isOpened()) {
        cout << "Im open" << endl;
    }

    while(true) {
        cap >> image;

        output << image;
        imshow("Display", image);

        int key = waitKey(25);
        if(key == 'q') {
            cout << "stopping video recording" << endl;
            break;
        }
    }

    cap.release();
    output.release();

    Mat replay;

    namedWindow("Check");
    
    VideoCapture testVid("vid/test.avi");

    if(!testVid.isOpened()) {
        cout << "Failed to open video file" << endl;
    } else {
        int fps = testVid.get(5);
        cout << fps << endl;
        int frameCount = testVid.get(7);

        while(testVid.isOpened()) {
            bool isFrame = testVid.read(replay);

            if(isFrame) {
                imshow("Check", replay);
            } else {
                cout << "No frame\n";
                break;
            }
            
            int key = waitKey(fps);
            if(key == 'q') {
                cout << "Stopping video" << endl;
                break;
            }
        }
    }

    testVid.release();
    destroyAllWindows();


    return 0;
}
