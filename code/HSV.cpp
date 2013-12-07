#include <cv.h>
#include <highgui.h> 
#include <iostream>
#include <fstream>

using namespace cv;
//乒乓HSV 5/15 100/255 70/255
//网球HSV 18/48 73/255 70/255
const int MaxHue = 48;
const int MinHue = 18;

const int MaxS = 255;
const int MinS = 73;

const int MaxV = 255;
const int MinV = 70;

const int TOLERANCE = 20;

bool sym(const Mat& img_HSV,uchar* data,int x,int y,int length);
void drawLine(Mat &img_tmp,int lengthOfmaxSerial,int indexOfmaxSerial);
void findBall(const Mat &img_HSV,const Mat &img, Mat &img_tmpOutput);
void refineVirginByColor(const Mat &img_edge, const Mat &img_HSV, Mat &img_tmpOutput, int nearThresh);
bool isNearHueOfBall(uchar* data, int slot, int nearThresh, const Mat& img_HSV);
bool isHueOfBall(int hue, int s, int v);
bool isOutOfBound(int slot, const Mat &img_HSV);
void HSV(const Mat &img, const Mat &img_edge, Mat &img_re);
void filterT(const Mat &img_HSV, Mat &img_re);


bool sym(const Mat& img_HSV,uchar* data,int slot,int length){
	int r = length/2;
	slot -= r;
	for(int i=0;i<r-TOLERANCE;++i){
		int up = slot-i*img_HSV.step[0];
		int down = slot+i*img_HSV.step[0];
		if(!isOutOfBound(up, img_HSV) && data[up]==255 && data[up+1]==255 && data[up+2]==255){
			return 0;
		}
		if(!isOutOfBound(down, img_HSV) && data[down]==255 && data[down+1]==255 && data[down+2]==255){
			return 0;
		}
	}

	int count_up = 0;
	int count_down = 0;
	int total_up = 0;
	int total_down = 0;
	for(int i=r+TOLERANCE;i<r+2*TOLERANCE;++i){
		int up = slot-i*img_HSV.step[0];
		int down = slot+i*img_HSV.step[0];
		if(!isOutOfBound(up, img_HSV)){
			++total_up;
			if(!(data[up]==255 && data[up+1]==255 && data[up+2]==255)){
				++count_up;
			}
		}
		if(!isOutOfBound(down, img_HSV)){
			++total_down;
			if(!(data[down]==255 && data[down+1]==255 && data[down+2]==255)){
				++count_down;
			}
		}
	}
	//std::cout<<count1<<" "<<count2<<std::endl;
	if(count_up>total_up*0.1 || count_down>total_down*0.1){
		return 0;
	}
	return 1;
}


void drawLine(Mat &img_tmp,int length,int x,int y){
	Point a = Point (y,x); 
	Point b = Point (y+length,x); 
	line(img_tmp,a,b,Scalar(0,0,255));
}


void findBall(const Mat &img_HSV, const Mat &img , Mat &img_tmpOutput)
{
	int lengthOfmaxSerial=0;
	int indexOfmaxSerial_x;
	int indexOfmaxSerial_y;
	int lengthOfcurrentSerial;
	int indexOfcurrentSerial_x;
	int indexOfcurrentSerial_y;

	Mat img_tmp = img.clone();
	
	uchar* dataOfTmpOutput = (uchar*)img_tmp.data;
	uchar* dataOfHSV = (uchar*)img_HSV.data;
	
	for (int i=0; i<img_HSV.rows; i++) {
		for (int j=0; j<img_HSV.cols; j++) {
			int slot = i*img_HSV.step[0]+j*img_HSV.step[1];
			if(j==0){
				indexOfcurrentSerial_x = i;
				indexOfcurrentSerial_y = j;
				lengthOfcurrentSerial = 0;
			}
			if(dataOfHSV[slot]==255 && dataOfHSV[slot+1]==255 & dataOfHSV[slot+2]==255){
				if(lengthOfcurrentSerial>lengthOfmaxSerial){
					if(sym(img_HSV,dataOfHSV,slot,lengthOfcurrentSerial)){
						lengthOfmaxSerial = lengthOfcurrentSerial;
						indexOfmaxSerial_x = indexOfcurrentSerial_x;
						indexOfmaxSerial_y = indexOfcurrentSerial_y;
					}
				}
				indexOfcurrentSerial_x = i;
				indexOfcurrentSerial_y = j;
				lengthOfcurrentSerial = 0;
			}
			else{
				++lengthOfcurrentSerial;
			}
		}
		if(lengthOfcurrentSerial>lengthOfmaxSerial){
			if(sym(img_HSV,dataOfHSV,i*img_HSV.step[0],lengthOfcurrentSerial)){
				lengthOfmaxSerial = lengthOfcurrentSerial;
				indexOfmaxSerial_x = indexOfcurrentSerial_x;
				indexOfmaxSerial_y = indexOfcurrentSerial_y;
			}
		}
	}
	drawLine(img_tmp,lengthOfmaxSerial,indexOfmaxSerial_x,indexOfmaxSerial_y);
	
	img_tmpOutput = img_tmp.clone();
}

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

void filterT(const Mat &img_HSV, Mat &img_re)
{
	Mat img_tmp;
	inRange(img_HSV, Scalar(MinHue, MinS, MinV), Scalar(MaxHue, MaxS, MaxV), img_tmp);
	img_re = img_tmp.clone();

}

bool isNearHueOfBall(uchar* data, int slot, int nearThresh, const Mat& img_HSV)
{
	if(isHueOfBall(data[slot], data[slot+1], data[slot+2])){
		return 1;	
	}
	for(int i=1;i<=nearThresh;++i){
		i *= 3;
		int left = slot-i;
		int right = slot+i;
		int up = slot-i*img_HSV.step[0];
		int down = slot+i*img_HSV.step[0];

		if(!isOutOfBound(left, img_HSV)){
			if(isHueOfBall(data[left], data[left+1], data[left+2])){
				return 1;
			}
		}
		if(!isOutOfBound(right, img_HSV)){
			if(isHueOfBall(data[right], data[right+1], data[right+2])){
				return 1;
			}
		}
		if(!isOutOfBound(up, img_HSV)){
			if(isHueOfBall(data[up], data[up+1], data[up+2])){
				return 1;
			}
		}
		if(!isOutOfBound(down, img_HSV)){
			if(isHueOfBall(data[down], data[down+1], data[down+2])){
				return 1;
			}
		}
	}
	return 0;
}


bool isHueOfBall(int hue, int s, int v)
{
	if(hue>=MinHue && hue<=MaxHue && s>=MinS && s<=MaxS && v >=MinV && v<= MaxV){
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
	Mat img_HSV,img_t1;
	cvtColor(img, img_HSV, CV_BGR2HSV);
	refineVirginByColor(img_edge, img_HSV, img_re, 0);
	//findBall(img_t1,img,img_re);
	//filterT(img_HSV, img_re);
}

/*
int main(int argc, const char** argv)
{
	//Mat img = imread(argv[1], 1);
	Mat img = imread("C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\t2_1.jpg", 1);
	Mat img_edge, img_re;
	
	HSV(img, img, img_re);
	namedWindow( "TEST", CV_WINDOW_AUTOSIZE );
  	imshow( "TEST", img_re );
  	
  	waitKey(0);
  	return 0;
}
*/




