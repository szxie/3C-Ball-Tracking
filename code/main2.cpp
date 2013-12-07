#include <cv.h>
#include <highgui.h> 
#include <iostream>

#include "Edge.cpp"
#include "HSV.cpp"
#include "Circle.cpp"

using namespace cv;

char WindName[] = "Circle";
char WindNameE[] = "Edge";
char WindNameH[] = "HSV";

int main(int argc, char *argv[])
{ 
	Mat img = imread(argv[1], 1);
	Mat img_cedge, img_HSV, img_circle;
	
	Edge(img, img_cedge);	
	//HSV(img, img_cedge, img_HSV);	
	Circle(img_cedge, img, img_circle);
		
	//delete
  	namedWindow( WindName, CV_WINDOW_AUTOSIZE );
  	namedWindow( WindNameE, CV_WINDOW_AUTOSIZE );
  	namedWindow( WindNameH, CV_WINDOW_AUTOSIZE );
  	imshow( WindName, img_circle );
	//imshow( WindNameE, img_cedge);
	//imshow( WindNameH, img_HSV);
	  	
  	//window

	//delete
	cvWaitKey(0);

	while (true);
  	//waitKey(0);
	return 0;

}
