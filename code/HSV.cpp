#include <cv.h>
#include <highgui.h> 
#include <iostream>
#include <fstream>

using namespace cv;

const int MaxHue = 20;
const int MinHue = 0;

void refineVirginByColor(const Mat &img_edge, const Mat &img_HSV, Mat &img_tmpOutput, int nearThresh);
bool isNearHueOfBall(uchar* data, int slot, int nearThresh, const Mat& img_HSV);
bool isHueOfBall(int hue);
bool isOutOfBound(int slot, const Mat &img_HSV);
void HSV(const Mat &img, const Mat &img_edge, Mat &img_re);

void refineVirginByColor(const Mat &img_edge, const Mat &img_HSV, Mat &img_tmpOutput, int nearThresh)
{
	Mat img_tmp = img_edge.clone();
	
	uchar* dataOfTmpOutput = (uchar*)img_tmp.data;
	uchar* dataOfHSV = (uchar*)img_HSV.data;
	
	for (int i=0; i<img_HSV.rows; i++) {
		for (int j=0; j<img_HSV.cols; j++) {
			int slot = i*img_HSV.step[0]+j*img_HSV.step[1];
			if(!isNearHueOfBall(dataOfHSV,slot,nearThresh, img_HSV)){
				dataOfTmpOutput[slot+0] = 255;
				dataOfTmpOutput[slot+1] = 255;
				dataOfTmpOutput[slot+2] = 255;
			}
		}
	}
	
	img_tmpOutput = img_tmp.clone();
}


bool isNearHueOfBall(uchar* data, int slot, int nearThresh, const Mat& img_HSV)
{
	if(isHueOfBall(data[slot])){
		return 1;	
	}
	for(int i=1;i<=nearThresh;++i){
		i *= 3;
		int left = slot-i;
		int right = slot+i;
		int up = slot-i*img_HSV.step[0];
		int down = slot+i*img_HSV.step[0];

		if(!isOutOfBound(left, img_HSV)){
			if(isHueOfBall(data[left])){
				return 1;
			}
		}
		if(!isOutOfBound(right, img_HSV)){
			if(isHueOfBall(data[right])){
				return 1;
			}
		}
		if(!isOutOfBound(up, img_HSV)){
			if(isHueOfBall(data[up])){
				return 1;
			}
		}
		if(!isOutOfBound(down, img_HSV)){
			if(isHueOfBall(data[down])){
				return 1;
			}
		}
	}
	return 0;
}


bool isHueOfBall(int hue)
{
	if(hue>=MinHue && hue<=MaxHue){
		return 1;
	}
	return 0;
}


bool isOutOfBound(int slot, const Mat &img_HSV){
	if(slot<0 || slot>=(img_HSV.rows * img_HSV.cols)){//doubt
		return 1;
	}
	return 0;
}

//img 原图，img_edge 修改依据，img_re 输出
void HSV(const Mat &img, const Mat &img_edge, Mat &img_re)
{
	Mat img_HSV;
	cvtColor(img, img_HSV, CV_BGR2HSV);
	refineVirginByColor(img_edge, img_HSV, img_re, 1);
}

/*
int main(int argc, const char** argv)
{
	Mat img = imread(argv[1], 1);
	Mat img_edge, img_re;
	
	HSV(img, img, img_re);
	namedWindow( "TEST", CV_WINDOW_AUTOSIZE );
  	imshow( "TEST", img_re );
  	
  	waitKey(0);
  	return 0;
}
*/




