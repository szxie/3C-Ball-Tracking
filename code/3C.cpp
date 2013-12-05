//Edge part
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include <iostream>
#include "EdgeF.h"
#include "HSVF.h"
#include "CircleF.h"

using namespace cv;

char WindName[] = "Circle";
char WindNameE[] = "Edge";
char WindNameH[] = "HSV";

int main(int argc, char *argv[])
{
 	IplImage* frame = NULL;
 	
	IplImage *debug;
	Mat img_circle;
	IplImage *img_cedge;
	IplImage *img_HSV;
	
	namedWindow( WindName, CV_WINDOW_NORMAL );
	//cvMoveWindow(WindName, 400, 100);
	
  	CvCapture* capture = cvCreateCameraCapture(-1);
	cvNamedWindow(WindNameE, 0);
    cvNamedWindow(WindNameH, 0);
    while( true ) {
    	frame = cvQueryFrame( capture );
    	if (!frame) break;
    	
    	cvFlip(frame, frame, 1);
    	debug = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
    	cvCopy(frame, debug);
    		
    	if (frame){
    		img_cedge = Edge(debug);
			img_HSV = HSV(debug, img_cedge);
			img_circle = Circle(img_HSV, debug);
		}
		else {
			printf("error--break");
			break;
		}
      	imshow(WindName,img_circle);
      	cvShowImage(WindNameE, img_cedge);
      	cvShowImage(WindNameH, img_HSV);
      	//cvShowImage(WindName, debug);
      	cvReleaseImage(&debug);
      	char c=cvWaitKey(33);
      	if(c==27)break;
  	}
  	cvReleaseCapture(&capture);
  	cvDestroyWindow(WindName);

 	return 0;
}

