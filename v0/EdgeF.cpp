//Edge part
#include <cv.h>
#include <highgui.h> 
#include <iostream>

using namespace std;

IplImage* Edge(IplImage* img)
{

	//create image
	IplImage* img_edge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* img_cedge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	//rgb to gray
	cvCvtColor(img, img_gray, CV_BGR2GRAY);
	
    
	cvCanny(img_gray, img_edge, (float)30, (float)90, 3);//note!

	cvZero(img_cedge);
	cvCopy(img, img_cedge, img_edge);
	cvNot(img_cedge, img_cedge);
	cvReleaseImage(&img_edge);
	cvReleaseImage(&img_gray);
    return img_cedge;    
}

