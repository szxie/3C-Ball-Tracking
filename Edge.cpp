//3C

#include <cv.h>
#include <highgui.h> 
#include <iostream>

using namespace std;
IplImage* img = NULL;
IplImage* img_gray = NULL;
IplImage* img_edge = NULL;//edge img without colour
IplImage* img_cedge = NULL;//edge img with colour
IplImage* img_tmp = NULL;//not used

char WindName[] = "Edge";
char TbarName[] = "Threshold";

void on_Tbar(int h)
{
	//doubt? 
	//cvSmooth(img_gray, img_tmp, CV_BLUR, 3, 3, 0, 0);
	
	//canny changeable
	cvCanny(img_gray, img_edge, (float)h, (float)h*3, 3);

	cvZero(img_cedge);
	cvCopy(img, img_cedge, img_edge);

	//smooth the result or not?
	//cvSmooth(img_cedge, img_tmp, CV_BLUR, 3, 3, 0, 0);
	cvShowImage(WindName, img_cedge);
	
	//save the img
	//cvNot(img_cedge, img_tmp);
	//cvSaveImage("outP.jpg", img_tmp);
	

}

void edge(char *fileN)
{
	int TbarV = 1;

	img = cvLoadImage(fileN, 1);
	if (!img) {
		cout << "Could not load image file " << fileN << endl; 
		exit(0);
	}

	//create image
	img_tmp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	img_edge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	img_cedge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	//rgb to gray
	cvCvtColor(img, img_gray, CV_BGR2GRAY);
	
	//window and tbar
	cvNamedWindow(WindName, 0);
	cvCreateTrackbar(TbarName, WindName, &TbarV, 100, on_Tbar);

	on_Tbar(0);

	//delete
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&img_edge);
	cvReleaseImage(&img_gray);
	cvReleaseImage(&img_cedge);
	cvDestroyWindow(WindName);

}

int main(int argc, char *argv[])
{
	edge(argv[1]);
	return 0;

}
