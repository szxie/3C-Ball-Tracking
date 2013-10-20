#include<cv.h>
#include<highgui.h>
#include<math.h>
int main(int argc,char**argv)
{
	IplImage*img=NULL;
	if(argc==2&&(img=cvLoadImage(argv[1],1))!=0)
	{
		IplImage* gray=cvCreateImage(cvGetSize(img),8,1);
		IplImage* color_dst = cvCreateImage( cvGetSize(img), 8, 3 );
		
		CvMemStorage* storage=cvCreateMemStorage(0);
	//	cvCanny( img, gray, 50, 200, 3 ); 
		cvCvtColor(img,gray,CV_BGR2GRAY);
		cvSmooth(gray,gray,CV_GAUSSIAN,9,9);
		CvSeq* circles=cvHoughCircles(gray,storage,CV_HOUGH_GRADIENT,2,gray->height/4,220,90,0,0);
		int i;
		for(i=0;i<circles->total;i++)
		{
			float* p=(float*)cvGetSeqElem(circles,i);
			cvCircle(img,cvPoint(cvRound(p[0]),cvRound(p[1])),3,CV_RGB(255,0,0),-1,8,0);
			cvCircle(img,cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]),CV_RGB(255,0,0),3,8,0);
		}
		cvNamedWindow("circles",1);
		cvShowImage("circles",img);

		cvWaitKey(-1); //等待按键
		
		// 解放
		cvReleaseImage(&img);
		cvReleaseImage(&gray);
		cvDestroyWindow("circles");
		
	}
	return 0;
}
