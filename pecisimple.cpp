#include "mySerial.h"
#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;
Mat imgGray;
Mat imgOri;
Mat imgThresh;
int main(int argc, char** argv)
{
	mySerial serial("/dev/ttyACM0",115200);
	vector<vector<cv::Point> > contours;
	vector<Vec4i> hierarchy;
	vector<vector<cv::Point>> bigkontur;
	Point2f center;
	vector<Vec3f> circles;
	float radius;
	//int h_min = 0, h_max = 255, s_min = 0, s_max = 255, v_min = 52, v_max = 255, conture = 100;
	//int iSliderValue1 = 50, iSliderValue2 = 50, param1 = 100, param2 = 72, minR = 0, maxR = 300;
	int h_min = 0, h_max = 255, s_min = 0, s_max = 124, v_min = 68, v_max = 255, Threshold = 115;
	int iSliderValue1 = 100, iSliderValue2 = 100, param1 = 20, param2 = 20, minR = 140, maxR = 212;
	int thresh = 0;
	int max_thresh = 255;

	int morphops(Mat &imgGray);

	VideoCapture Kamera;
	Kamera.open(0);
	Kamera.set(CV_CAP_PROP_FRAME_WIDTH, 320);//420);
	Kamera.set(CV_CAP_PROP_FRAME_HEIGHT, 240);//340);
	while (1)
	{

		namedWindow("Trackbar Window", CV_WINDOW_NORMAL);
		createTrackbar("R1_MIN: ", "Trackbar Window", &h_min, 255);
		createTrackbar("R1_MAX: ", "Trackbar Window", &h_max, 255);
		createTrackbar("de: ", "Trackbar Window", &s_min, 255);
		createTrackbar("ad: ", "Trackbar Window", &s_max, 255);
		createTrackbar("dde: ", "Trackbar Window", &v_min, 255);
		createTrackbar("fff: ", "Trackbar Window", &v_max, 255);
		createTrackbar("Threshold:", "Trackbar Window", &thresh, max_thresh);
		createTrackbar("Brightness", "Trackbar Window", &iSliderValue1, 100);
		createTrackbar("Contrast", "Trackbar Window", &iSliderValue2, 100);
		createTrackbar("param1", "Trackbar Window", &param1, 300);
		createTrackbar("param2", "Trackbar Window", &param2, 300);
		createTrackbar("minRadius", "Trackbar Window", &minR, 300);
		createTrackbar("maxRadius", "Trackbar Window", &maxR, 300);

		int iBrightness = iSliderValue1 - 50;
		double dContrast = iSliderValue2 / 50.0;
		imgOri.convertTo(imgOri, -1, dContrast, iBrightness);

		Kamera.read(imgOri);
		cvtColor(imgOri, imgGray, CV_BGR2HSV);
		//GaussianBlur(imgGray, imgGray, cv::Size(9, 9), 2, 2);
		medianBlur(imgGray, imgGray, 3);
		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(5, 5));
		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5, 5));

		erode(imgGray, imgGray, erodeElement);
		dilate(imgGray, imgGray, dilateElement);

		inRange(imgGray, Scalar(h_min, s_min, v_min), Scalar(h_max, s_max, v_max), imgThresh);
		threshold(imgThresh, imgGray, thresh, max_thresh,THRESH_OTSU);
		
		vector<Vec3f> circles;

double dparam1 = param1 / 1.0;
double dparam2 = param2 / 1.0;

HoughCircles(imgGray, circles, HOUGH_GRADIENT, 2,imgGray.rows / 16, param1,	param2, minR, maxR);
int gg = 0;
//char ee;
std::cout<<"done1";
	for (size_t i = 0; i < circles.size(); i++)
	{
		std::cout<<"masuk";
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		circle(imgOri, center, 1, Scalar(0, 100, 100), 3, LINE_AA);

		
		int radius = c[2];
		printf("Radius = %d",radius);
		//sprintf(ee, "rds = %d", radius);
		circle(imgOri, center, radius, Scalar(255, 255, 255), 3, LINE_AA);
		line(imgOri, center, Point(center.x+radius,center.y+radius), Scalar(110, 220, 0), 3, LINE_AA);

		if (radius <=170){
			circle(imgOri, Point(10, 10), 10, Scalar(255, 255, 0), 3, LINE_AA);
			serial.Send(6);
		}
		else if (radius >=172 && radius <=177 ){
			circle(imgOri, Point(10, 50), 10, Scalar(255, 255, 255), 3, LINE_AA);
			serial.Send(5);
		}
		else if (radius >=181 ){
			circle(imgOri, Point(10, 100), 10, Scalar(255, 0, 255), 3, LINE_AA);
			serial.Send(4);
		}
		else {
			serial.Send(3);
			std::cout<<"\n tidak terdeteksi"<<endl;
			}
	}
	

	//putText(imgOri, gg, Point(10, 10), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 0, 255, 255));
	imshow("detected circles", imgOri);
	imshow("detected ", imgGray);

	if (waitKey(30) == 27)break;
	}
	return 0;
}
