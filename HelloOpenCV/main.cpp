//
//  main.cpp
//  HelloOpenCV
//
//  Created by Csaba Trucza on 22/12/15.
//  Copyright © 2015 Csaba Trucza. All rights reserved.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int process(VideoCapture& capture) {
    int n = 0;
    char filename[200];
    string window_name = "video | q or esc to quit";
    cout << "press space to save a picture. q or esc to quit" << endl;
    namedWindow(window_name, WINDOW_KEEPRATIO); //resizable window;
    Mat frame;
    
    for (;;) {
        capture >> frame;
        if (frame.empty())
            break;
        
        imshow(window_name, frame);
        char key = (char)waitKey(1); //delay N millis, usually long enough to display and capture input
        
        switch (key) {
            case 'q':
            case 'Q':
            case 27: //escape key
                return 0;
            case ' ': //Save an image
                sprintf(filename,"filename%.3d.jpg",n++);
                imwrite(filename,frame);
                cout << "Saved " << filename << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}

int main(int ac, char** av) {
    
//    if (ac != 2) {
//        return 1;
//    }
    std::string arg = "/Users/ctrucza/Desktop/1.mp4"; //av[1];
    VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file or image sequence
    if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
        capture.open(atoi(arg.c_str()));
    if (!capture.isOpened()) {
        cerr << "Failed to open the video device, video file or image sequence!\n" << endl;
        return 1;
    }
    return process(capture);
}