#include <cv.h>
#include <highgui.h> 
#include <iostream>

#include "Edge.h"
#include "HSV.h"
#include "Circle.h"

using namespace cv;

char WindName[] = "Circle";
char WindNameE[] = "Edge";
char WindNameH[] = "HSV";

int main(int argc, char *argv[])
{
 	Mat frame;
	Mat debug;

	Mat img_cedge;
	Mat img_HSV;	 	
	Mat img_circle;
	Mat img_circle2;
	
	namedWindow( WindName, CV_WINDOW_NORMAL );
	namedWindow( WindNameE, CV_WINDOW_NORMAL );
  	namedWindow( WindNameH, CV_WINDOW_NORMAL );
  	
  	CvCapture* capture = cvCreateCameraCapture(-1);

    while( true ) {
    	frame = cvQueryFrame( capture );
    	
    	flip(frame, frame, 1);
    	debug = frame.clone();
    		
    	if (!frame.empty()){
    		//Edge(debug, img_cedge);
    		img_cedge = debug;
    		HSV(debug, img_cedge, img_HSV);
    		Circle(img_HSV, debug, img_circle);
    		Circle(img_HSV, img_HSV, img_circle2);
		}
		else {
			printf("error--break");
			break;
		}
      	imshow(WindName,img_circle);
      	imshow(WindNameE, img_cedge);
      	imshow(WindNameH, img_circle2);
      	
      	char c=cvWaitKey(10);
      	if(c==27)break;
  	}
 	return 0;
}

