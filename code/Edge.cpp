//Edge part
 #include <opencv2/opencv.hpp> 
#include <iostream>
const int MAX = 90;
const int MIN = 30;
using namespace cv;

void Edge(const Mat &img, Mat &img_re)
{
	Mat img_gray, img_edge, img_cedge;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	Canny(img_gray, img_edge, (float)MIN, (float)MAX, 3);
	
	img_cedge.zeros(img.size(), img.type());
	img.copyTo(img_cedge, img_edge);
	bitwise_not(img_cedge, img_cedge);
	
	img_re = img_cedge.clone();
	
}

/*
int main(int argc, const char** argv)
{
	Mat img = imread(argv[1], 1);
	Mat img_cedge;
	Edge(img, img_cedge);
	
	namedWindow( "TEST", CV_WINDOW_AUTOSIZE );
  	imshow( "TEST", img_cedge );
  	
  	waitKey(0);
  	return 0;
}
*/
