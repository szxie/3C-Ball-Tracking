#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <stdio.h>
#include <math.h>
void Sobel(IplImage*, IplImage*);
int main()
{
    CvCapture *capture;
    IplImage *src,*feature,*srcYcc,*featureYcc,*result;
    CvPoint2D32f center;
    CvMemStorage* storage = NULL;
    CvMat *A=cvCreateMat(2,3,CV_32FC1);
    CvSeq* circles = NULL;
    float radius ;
    capture =cvCaptureFromCAM(0) ;
    cvNamedWindow("Webcam",0);
   // cvNamedWindow("Webcam2",0);
    float YRange[2],CrRange[2],CbRange[2];
     
    while(TRUE)
    {
        int i,X_POS,Y_POS; 
        CvScalar  color;
        src = cvQueryFrame(capture);
        srcYcc = cvCreateImage(cvGetSize(src) ,IPL_DEPTH_8U ,3);
        result = cvCreateImage(cvGetSize(src) ,IPL_DEPTH_8U ,1);
        feature = cvLoadImage("compare.jpg", CV_LOAD_IMAGE_COLOR);                                                                                                                                                                    
                    featureYcc= cvCreateImage(cvGetSize(feature) ,IPL_DEPTH_8U ,3);
         
        cvCvtColor(src,srcYcc, CV_BGR2YCrCb);
        cvCvtColor(feature,featureYcc, CV_BGR2YCrCb);
         for (Y_POS = 0; Y_POS < feature->height; Y_POS++) {
            for (X_POS = 0; X_POS < feature->width; X_POS++) {
                color = cvGet2D(featureYcc,Y_POS,X_POS);
                if (Y_POS ==0 && X_POS ==0) {
                            YRange[0] = YRange[1] = color.val[0];
                            CrRange[0] = CrRange[1] = color.val[1];
                            CbRange[0] = CbRange[1] = color.val[2];
                } else {
                if (color.val[0] < YRange[0])YRange[0] = color.val[0];
                if (color.val[0] > YRange[1])YRange[1] = color.val[0];
                if (color.val[1] < CrRange[0])CrRange[0] = color.val[1];
                if (color.val[1] > CrRange[1])CrRange[1] = color.val[1];
                if (color.val[2] < CbRange[0])CbRange[0] = color.val[2];
                if (color.val[2] > CbRange[1])CbRange[1] = color.val[2];
                }
            }
        }
        for (Y_POS = 0; Y_POS < srcYcc->height; Y_POS++) {
            for (X_POS = 0; X_POS < srcYcc->width; X_POS++) {
                color = cvGet2D(srcYcc,Y_POS,X_POS);
                if (color.val[0]>YRange[0]     && color.val[0]<YRange[1]  &&
                    color.val[1]>CrRange[0] && color.val[1]<CrRange[1] &&
                    color.val[2]>CbRange[0] && color.val[2]<CbRange[1])
                    cvSet2D(result,Y_POS,X_POS,CV_RGB(255,255,255));
                else
                    cvSet2D(result,Y_POS,X_POS,CV_RGB(0,0,0));            
            }
        }
        cvDilate(result,result,NULL,5);
        cvSmooth(result,result,CV_GAUSSIAN,51,0,0,0);    
                                 
         
        storage = cvCreateMemStorage(0);  
        circles = cvHoughCircles(result, storage, CV_HOUGH_GRADIENT,1, 100, 50, 50,10,MAX (result->width, result->height));   
        for    (i = 0; i < circles->total; i++ )  
        {  
            float* p = (float*)cvGetSeqElem(circles, i );
            cvCircle(src, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );  
        }
        cvShowImage("Webcam",src);
        //cvShowImage("Webcam2",result);
         
        if    (cvWaitKey(10)>=0)
        {
            break;
        }
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("Webcam");
    cvDestroyWindow("Webcam2");
    cvReleaseImage(&src);
    cvReleaseImage(&feature);
    cvReleaseImage(&srcYcc);
    cvReleaseImage(&featureYcc);
    cvReleaseImage(&result);
     
}
void Sobel(IplImage* src, IplImage* dst) 
{
     double v1, v2, v;
     int X_POS, Y_POS;
     IplImage *H = cvCreateImage(cvGetSize(src), 32, 1); 
     IplImage *V = cvCreateImage(cvGetSize(src), 32, 1); 
     IplImage *HV = cvCreateImage(cvGetSize(src), 32, 1); 
     cvSobel(src,H,0,1,3);
     cvSobel(src,V,1,0,3);
     for (Y_POS = 0; Y_POS < src->height; Y_POS++) {
          for (X_POS = 0; X_POS < src->width; X_POS++) {    
               v1 = cvGetReal2D(H, Y_POS, X_POS);
               v2 = cvGetReal2D(V, Y_POS, X_POS);
               v = sqrt(v1 * v1 + v2 * v2);
               cvSetReal2D(HV,Y_POS,X_POS,v);
          }      
     }
     cvNormalize(HV,dst,0,255,CV_MINMAX,0);
     cvReleaseImage(&H);
     cvReleaseImage(&V);
     cvReleaseImage(&HV);
      
}
