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
    int fps = 25;
    
    output.open("~/proj_vids/test.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), fps, frameSize);
    if(output.isOpened) {
        cout << "Im open" << endl;
    }


    while(true) {
        cap >> image;

        output.write(image);
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
    
    VideoCapture testVid("~/proj_vids/test.mp4");

    if(!testVid.isOpened()) {
        cout << "Failed to open video file" << endl;
    } else {
        int fps = testVid.get(5);
        int frameCount = testVid.get(7);

        while(testVid.isOpened()) {
            bool isFrame = testVid.read(replay);

            if(isFrame) {
                imshow("Check", replay);
            } else {
                cout << "No frame\n";
                break;
            }
            
            int key = waitKey(25);
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
