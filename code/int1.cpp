/*程序可以将黄色的乒乓球，在光线不太亮的情况下，准确的识别出来，并返回圆心坐标 */
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv/cv.h>
#include<iostream>
#include<stdio.h>
using namespace std;
using namespace cv;
	CvCapture* capture=0;
	IplImage* image;
	void Hough(IplImage*);
int main(void)
{
	capture=cvCaptureFromCAM(0);
	cvNamedWindow("result",1);
	cvNamedWindow("f",2);
for(;;)
{
	IplImage* image=cvQueryFrame(capture);
cvShowImage("f",image);
/*下面这个循环是预处理，将除了黄色的区域都变成黑色，方便圆的识别
首先提取图像的RGB值，if判断是否是黄色，如果不是将其变成黑色即R=0，G=0，B=0*/
for(int row=0;row<image->height;row++)
	{
		for(int col=0;col<image->widthStep;col=col+3)
		{
int B = CV_IMAGE_ELEM(image, unsigned char, row, col*3+0);
int G = CV_IMAGE_ELEM(image, unsigned char, row, col*3+1);
int R = CV_IMAGE_ELEM(image, unsigned char, row, col*3+2);
			if((B<=100)&&(G>=100)&&(G<=200)&&(R>200))
			{
			}
			else
			{
			CV_IMAGE_ELEM(image, unsigned char, row, col*3+0) = 0;

			CV_IMAGE_ELEM(image, unsigned char, row, col*3+1) = 0;

			CV_IMAGE_ELEM(image, unsigned char, row, col*3+2) = 0;
			}
		}
	}

cvShowImage("result",image);
Hough(image);
if(waitKey(10)>=0)
return 0;

}
}
/*将处理过的图像经过高斯变化后，找出圆，并返回圆心*/
void Hough(IplImage* img)
        {
        IplImage* gray=cvCreateImage(cvGetSize(img),8,1);
        CvMemStorage* storage=cvCreateMemStorage(0);
        cvCvtColor(img,gray,CV_BGR2GRAY);
        cvSmooth(gray,gray,CV_GAUSSIAN,9,9);
        CvSeq* circles=cvHoughCircles(gray,storage,CV_HOUGH_GRADIENT,2,gray->height/4,200,100);
        int i;
        cout<<circles->total;
        for(i=0;i<circles->total;i++)
        {
        float* p=(float*)cvGetSeqElem(circles,i);
        cvCircle(img,cvPoint(cvRound(p[0]),cvRound(p[1])),3,CV_RGB(0,255,0),-1,8,0);
        cvCircle(img,cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]),CV_RGB(0,255,0),3,8,0);
        cvNamedWindow("circles",2);
	cvShowImage("circles",img);
        cout<<"圆心坐标x="<<cvRound(p[0])<<endl<<"圆心坐标y="<<cvRound(p[1])<<endl;
        cout<<"半径="<<cvRound(p[2])<<endl;
}
}

