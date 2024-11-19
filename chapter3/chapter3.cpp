#include "chapter3.h"

/*图像反转*/
void MyMethod::Image_inversion(cv::Mat& src, cv::Mat& dst)
{
	int nr = src.rows;
	int nc = src.cols * src.channels();
	src.copyTo(dst);
	if (src.isContinuous() && dst.isContinuous()) {  //判断图像连续性
		nr = 1;
		nc = src.rows * src.cols * src.channels(); //行数*列数 * 通道数=一维数组的个数
	}

	for (int i = 0; i < nr; i++) {
		const uchar* srcdata = src.ptr <uchar>(i);  //采用指针访问像素，获取第i行的首地址
		uchar* dstdata = dst.ptr <uchar>(i);
		for (int j = 0; j < nc; j++) {
			dstdata[j] = 255 - srcdata[j]; //开始处理每个像素
		}
	}
}



/*对数变换方法1*(适用于灰度图像)*/
cv::Mat MyMethod::LogTransform(cv::Mat& src, double c) {
	if (src.channels() > 1)
		cv::cvtColor(src, src, CV_RGB2GRAY);
	cv::Mat dst;
	src.copyTo(dst);
	dst.convertTo(dst, CV_64F);
	dst = dst + 1.0;
	cv::log(dst, dst);
	dst = c * dst;
	cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX); //经过对比拉升（将像素值归一化到0-255）得到最终的图像
	dst.convertTo(dst, CV_8U);  //转回无符号8位图像
	return dst;

}

//幂律变换
void MyMethod::powerLawTransform(const cv::Mat& src, cv::Mat& dst, double gamma, double c ) {
	CV_Assert(gamma > 0);  // 确保 gamma 是正数

	// 将源图像转换为浮点型，并归一化到 [0, 1] 范围
	cv::Mat srcFloat;
	src.convertTo(srcFloat, CV_32F, 1.0 / 255.0); // 确保 srcFloat 是 CV_32F 类型

	// 进行幂律变换
	cv::Mat transformed;
	cv::pow(srcFloat, gamma, transformed); // cv::pow 的输出是浮点类型

	// 应用比例常数 c
	transformed = c * transformed;

	// 将结果图像转换回 [0, 255] 范围
	transformed.convertTo(dst, CV_8U, 255.0); // 转换回 8 位图像
}




void MyMethod::contrastStretching(const Mat& input, Mat& output, int r1, int s1, int r2, int s2)
{
	output = input.clone(); //复制输入图像

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			uchar pixel = input.at<uchar>(i, j);//当前像素值
			if (pixel <= r1) {
				output.at<uchar>(i, j) = static_cast<uchar>((float)s1 / r1 * pixel);
			}
			else if (pixel <= r2) {
				output.at<uchar>(i, j) = static_cast<uchar>((float)(s2 - s1) / (r2 - r1) * (pixel - r1) + s1);
			}
			else {
				output.at<uchar>(i, j) = static_cast<uchar>((float)(255 - s2) / (255 - r2) * (pixel - r2) + s2);
			}

		}
	}
}

// 分段线性变换函数 - 灰度级分层
void MyMethod::grayLevelSlicing(const Mat& input, Mat& output, int lowerBound, int upperBound, uchar highlightValue, uchar backgroundValue) {
	output = Mat::zeros(input.size(), input.type()); // 初始化输出图像

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			uchar pixel = input.at<uchar>(i, j); // 获取当前像素值

			// 灰度级分层逻辑
			if (pixel >= lowerBound && pixel <= upperBound) {
				output.at<uchar>(i, j) = highlightValue; // 突出显示的灰度值
			}
			else {
				output.at<uchar>(i, j) = backgroundValue; // 背景灰度值
			}
		}
	}
}

// 比特平面分层函数
void MyMethod::bitPlaneSlicing(const Mat& input, vector<Mat>& bitPlanes) {
	// 初始化比特平面数组
	for (int k = 0; k < 8; k++) {
		Mat plane = Mat::zeros(input.size(), CV_8U); // 每个比特平面
		for (int i = 0; i < input.rows; i++) {
			for (int j = 0; j < input.cols; j++) {
				// 获取当前像素值的第 k 位
				uchar pixel = input.at<uchar>(i, j);
				uchar bit = (pixel >> k) & 1; // 提取第 k 位（0 或 1）
				plane.at<uchar>(i, j) = bit * 255; // 将 1 转换为 255，0 保持为 0
			}
		}
		bitPlanes.push_back(plane); // 保存到比特平面数组
	}
}


//盒式核 空间滤波
void MyMethod::BoxKernel(const Mat& input, Mat& output, int kernelSize)
{
	// 创建盒式核（均值滤波）
	Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
	// 应用滤波器
	filter2D(input, output, -1, kernel);
}


//拉普拉斯锐化图像
void MyMethod::myLaplacian(const Mat& input, Mat& output)
{
	Mat laplacian;
	// 拉普拉斯滤波
	Laplacian(input, laplacian, CV_16S, 3); // 使用3x3核，输出16位以避免溢出
	convertScaleAbs(laplacian, laplacian);  // 将结果转换为8位图像
	// 锐化图像：原图 - 拉普拉斯结果
	output = input + laplacian;
}



