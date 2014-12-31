#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <string>
#include <sstream>
#include <signal.h>
using namespace cv;
using namespace std;
#define IN_WIN "Drawing..."

Mat img;

// CallBack Function for mouse events
void cbMouse(int event, int x, int y, int flags, void* userdata) {

static int imark=0;
    char textm[] = "mark999";

    if (event == EVENT_LBUTTONDOWN) { // Left mouse button pressed
circle(img, Point(x, y), 4, Scalar(0,0,255), 2);
imark++;// Increment the number of marks
sprintf(textm, "mark %d", imark);// Set the mark text
putText(img, textm, Point(x+6, y), FONT_HERSHEY_PLAIN,
                1, Scalar(0,0,0),2);
imshow(IN_WIN, img); // Show final image
    }
    return;
}

int main(int argc, char* argv[]) {

    // (omitted for brevity)	
    img = imread(argv[1]); //open and read the image
    // (omitted for brevity)
    namedWindow(IN_WIN);
    setMouseCallback(IN_WIN, cbMouse, NULL);
    imshow(IN_WIN, img);
    cout << "Pres any key to exit..." << endl;
    waitKey();
    return 0;
}