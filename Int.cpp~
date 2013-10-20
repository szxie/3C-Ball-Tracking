#include <cv.h>
#include <highgui.h> 
#include <iostream>

using namespace cv;
IplImage* img = NULL;
IplImage* img_gray = NULL;
IplImage* img_edge = NULL;//edge img without colour
IplImage* img_cedge = NULL;//edge img with colour
IplImage* img_tmp = NULL;//not used

/** @function main */
int main(int argc, char** argv)
{

  	/// Read the image
  	img = cvLoadImage( argv[1], 1 );

  	//create image
	img_tmp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	img_edge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	img_cedge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);

  	/// Convert it to gray
  	cvCvtColor( img, img_gray, CV_BGR2GRAY );

  	CvMemStorage* storage=cvCreateMemStorage(0);  
    	//cvSmooth(image0,image,CV_GAUSSIAN,5,5);  
    	CvSeq* results=cvHoughCircles(img_gray,storage,CV_HOUGH_GRADIENT,1,img_gray->width/8, 200, 100, 0, 0);  
    	
	for(int i=0;i<results->total ;i++)  
    	{  
       	 	float* p=(float*) cvGetSeqElem(results,i);  
        	CvPoint pt=cvPoint(cvRound(p[0]),cvRound(p[1]));  
       	 	cvCircle(img_tmp,pt,cvRound(p[2]),CV_RGB(255,0,0));  
    	}  
    	cvNamedWindow("source",0);  
   	cvShowImage("source",img_gray);  
   	cvNamedWindow("cvHoughCircles",0);  
  	cvShowImage("cvHoughCircles",img_tmp);  
   	cvWaitKey(0);  
    	return 0;  

}
