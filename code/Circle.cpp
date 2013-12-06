#include <cv.h>
#include <highgui.h> 
#include <iostream>

using namespace cv;

//依据src1来找圆，输出图依照src2，结果为srcorin
void Circle(const Mat &src1, const Mat &src2, Mat &srcorin)
{
	Mat src_gray;
	srcorin = src2.clone();
    /// Convert it to gray
    cvtColor( src1, src_gray, CV_BGR2GRAY );

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
  
    //HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 3, src_gray.rows/10, 100, src_gray.rows/5, 0, src_gray.rows/2);
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 3, src_gray.rows/10, 100, src_gray.rows/5, 0, 0);
    for( size_t i = 0; i < circles.size(); i++ )
    {
        std::cout<<cvRound(circles[i][0])<<' '<<cvRound(circles[i][1])<<' '<<cvRound(circles[i][2])<<std::endl;
	}
  /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( srcorin, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( srcorin, center, radius, Scalar(0,0,255), 1, 8, 0 );
    }
}

/*
int main(int argc, const char** argv)
{
	Mat img = imread(argv[1], 1);
	Mat img2 = imread(argv[1], 1);
	Mat img_re;
	Circle(img, img2, img_re);
	
	namedWindow( "TEST", CV_WINDOW_AUTOSIZE );
  	imshow( "TEST", img_re );
  	
  	waitKey(0);
  	return 0;
}
*/
