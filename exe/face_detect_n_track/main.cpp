#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "VideoFaceDetector.h"

const cv::String    WINDOW_NAME("Camera video");
const cv::String    CASCADE_FILE("haarcascade_frontalface_default.xml");

int main(int argc, char** argv)
{

	cv::namedWindow(WINDOW_NAME, cv::WINDOW_KEEPRATIO | cv::WINDOW_AUTOSIZE);

	VideoFaceDetector detector(CASCADE_FILE);
	cv::Mat frame = cv::imread("timg.jpg", -1);
	double fps = 0, time_per_frame;
	//while (true)
	{
		auto start = cv::getCPUTickCount();
		detector.detectFace(frame);
		auto end = cv::getCPUTickCount();

		time_per_frame = (end - start) / cv::getTickFrequency();
		fps = (15 * fps + (1 / time_per_frame)) / 16;

		printf("Time per frame: %3.3f\tFPS: %3.3f\n", time_per_frame, fps);

		if (detector.isFaceFound())
		{
			cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
			cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));
		}
		
		cv::imshow(WINDOW_NAME, frame);
		//if (cv::waitKey(25) == 27) 
		//	break;
	}

	return 0;
}