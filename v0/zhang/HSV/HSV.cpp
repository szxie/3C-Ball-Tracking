#include "stdafx.h"
#include <cv.h>
#include <highgui.h> 
#include <iostream>
#include <fstream>

using namespace std;
IplImage* img = NULL;
IplImage* img_edge = NULL;
IplImage* img_HSV = NULL;

char WindName[] = "Edge";
char TbarName[] = "nearThresh";
const int MaxHue = 20;
const int MinHue = 0;

void refineVirginByColor(int nearThresh);
bool isNearHueOfBall(uchar* data, int slot, int nearThresh);
bool isHueOfBall(int hue);
bool isOutOfBound(int slot);
void detectHueRange(int thresh);
void edge(char *fileN1,char *fileN2);

void refineVirginByColor(int nearThresh)
{
	IplImage* img_tmpOutput;
	img_tmpOutput = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCopy(img_edge,img_tmpOutput);
	uchar* dataOfTmpOutput=(uchar*)img_tmpOutput->imageData;
	uchar* dataOfHSV=(uchar*)img_HSV->imageData;

	for(int i=0;i<img_HSV->height;i++){
		for(int j=0;j<img_HSV->width;j++){
			int slot = i*img_HSV->widthStep+j*img_HSV->nChannels;
			if(!isNearHueOfBall(dataOfHSV,slot,nearThresh)){
				dataOfTmpOutput[slot+0] = 255;
				dataOfTmpOutput[slot+1] = 255;
				dataOfTmpOutput[slot+2] = 255;
			}
		}
	}
	
	cvShowImage(WindName, img_tmpOutput);
	cvSaveImage("outP.jpg", img_tmpOutput);
}


bool isNearHueOfBall(uchar* data, int slot, int nearThresh){
	if(isHueOfBall(data[slot])){
		return 1;	
	}
	for(int i=1;i<=nearThresh;++i){
		i *= 3;
		int left = slot-i;
		int right = slot+i;
		int up = slot-i*img_HSV->widthStep;
		int down = slot+i*img_HSV->widthStep;

		if(!isOutOfBound(left)){
			if(isHueOfBall(data[left])){
				return 1;
			}
		}
		if(!isOutOfBound(right)){
			if(isHueOfBall(data[right])){
				return 1;
			}
		}
		if(!isOutOfBound(up)){
			if(isHueOfBall(data[up])){
				return 1;
			}
		}
		if(!isOutOfBound(down)){
			if(isHueOfBall(data[down])){
				return 1;
			}
		}
	}
	return 0;
}


bool isHueOfBall(int hue){
	if(hue>=MinHue && hue<=MaxHue){
		return 1;
	}
	return 0;
}


bool isOutOfBound(int slot){
	if(slot<0 || slot>=img_HSV->imageSize){
		return 1;
	}
	return 0;
}


void detectHueRange(int thresh)
{
	IplImage* img_cedge;
	img_cedge = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCopy(img_edge,img_cedge);
	uchar* data1=(uchar*)img_cedge->imageData;
	uchar* data2=(uchar*)img_HSV->imageData;
	
	for(int i=0;i<img_cedge->height;i++){
		for(int j=0;j<img_cedge->width;j++){
			if(data2[i*img_cedge->widthStep+j*img_cedge->nChannels+0] < thresh*20 || data2[i*img_cedge->widthStep+j*img_cedge->nChannels+0]>=thresh*20+20){
			//if(data2[i*img_cedge->widthStep+j*img_cedge->nChannels+0] != thresh){
				data1[i*img_cedge->widthStep+j*img_cedge->nChannels+0] = 255;
				data1[i*img_cedge->widthStep+j*img_cedge->nChannels+1] = 255;
				data1[i*img_cedge->widthStep+j*img_cedge->nChannels+2] = 255;
			}
		}
	}

	cvShowImage(WindName, img_cedge);
	cvReleaseImage(&img_cedge);

}


void edge(char *fileN1,char *fileN2)
{
	int TbarV = 0;

	img = cvLoadImage(fileN1, 1);
	img_edge = cvLoadImage(fileN2, 1);
	
	if (!img) {
		cout << "Could not load image file " << fileN1 << endl; 
		exit(0);
	}
	if (!img_edge) {
		cout << "Could not load image file " << fileN2 << endl; 
		exit(0);
	}

	img_HSV = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCvtColor( img, img_HSV, CV_BGR2HSV ); 
	
	cvNamedWindow(WindName, 0);
	cvCreateTrackbar(TbarName, WindName, &TbarV, 20, refineVirginByColor);
	refineVirginByColor(0);

	//delete
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&img_edge);
	cvReleaseImage(&img_HSV);
	cvDestroyWindow(WindName);

}

int main(int argc, char *argv[])
{
	edge(argv[1],argv[2]);
	return 0;
}
