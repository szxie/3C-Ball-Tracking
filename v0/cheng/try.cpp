#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray, srcorin;

  /// Read the image
  src = imread( argv[1], 1 );
  srcorin = imread(argv[2], 1);

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 3, src_gray.rows/10, 100, src_gray.rows/5, 0, src_gray.rows/2);
    for( size_t i = 0; i < circles.size(); i++ )
  {
  std::cout<<cvRound(circles[i][0])<<' '<<cvRound(circles[i][1])<<' '<<cvRound(circles[i][2])<<std::endl;
	}
  //std::cout<<src_gray.rows<<std::endl;
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

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", srcorin );


  waitKey(0);
  return 0;
}