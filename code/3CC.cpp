//Edge part
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include <iostream>
#include "EdgeF.cpp"
#include "HSVF.cpp"
#include "CircleF.cpp"

using namespace cv;

char WindName[] = "Circle";
char WindNameE[] = "Edge";
char WindNameH[] = "HSV";

int main(int argc, char *argv[])
{ 
	IplImage *img = cvLoadImage(argv[1], 1);
	IplImage *img_cedge = Edge(img);
	
	IplImage *img_HSV = HSV(img, img_cedge);
	
	Mat img_circle = Circle(img_HSV, img);
	
	//delete
  	namedWindow( WindName, CV_WINDOW_AUTOSIZE );
  	imshow( WindName, img_circle );
  	
  	//window
	cvNamedWindow(WindNameE, 0);
	cvShowImage(WindNameE, img_cedge);
	cvNamedWindow(WindNameH, 0);
	cvShowImage(WindNameH, img_HSV);

	//delete
	cvWaitKey(0);
	cvDestroyWindow(WindName);


  	waitKey(0);
	return 0;

}
