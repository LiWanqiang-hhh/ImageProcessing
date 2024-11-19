#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace cv;
using namespace std;

class MyMethod {
public:
	/*图像反转*/
	void Image_inversion(cv::Mat& src, cv::Mat& dst);
	
	/*对数变换 灰度*/
	Mat LogTransform(cv::Mat& src, double c);

	/*幂律变换*/
	void powerLawTransform(const cv::Mat& src, cv::Mat& dst, double gamma, double c = 1.0);

	//分段线性变换函数，对比度拉伸
	void contrastStretching(const Mat& input, Mat& output, int r1, int s1, int r2, int s2);
	
	//分段线性变换函数  灰度级分层
	void grayLevelSlicing(const Mat& input, Mat& output, int lowerBound, int upperBound, uchar highlightValue, uchar backgroundValue);

	// 比特平面分层函数
	void bitPlaneSlicing(const Mat& input, vector<Mat>& bitPlanes);

	//盒式核 空间滤波
	void BoxKernel(const Mat& input, Mat& output, int kernelSize);

	//拉普拉斯锐化图像
	void myLaplacian(const Mat& input, Mat& output);
};