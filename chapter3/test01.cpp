#include"chapter3.h"


int main() {
	cv::Mat src = cv::imread("BoxKernel.png", cv::IMREAD_GRAYSCALE);
	if (src.empty()) {
		return -1;
	}
	cv::Mat dst;

	// 存储比特平面
	vector<Mat> bitPlanes;

	MyMethod mm;
	//mm.Image_inversion(src, dst); //3.2.1图像反转 breast.png
	
	//dst = mm.LogTransform(src,10); //3.2.2对数变换2 FourierSpectrum.png
	
	//mm.powerLawTransform(src, dst, 5.0);  //幂律（伽马）变换 powerLawTransform.png

	//mm.contrastStretching(src, dst, 70, 60, 180, 220);  //分段线性变换函数，对比度拉伸  

	//mm.grayLevelSlicing(src, dst, 180, 200, 210, 20); //分段线性变换函数 - 灰度级分层  grayLevelSlicing.png

	//mm.bitPlaneSlicing(src, bitPlanes); //比特平面分层 bitPlaneSlicing.png

	//mm.BoxKernel(src, dst, 5); //盒式核 空间滤波  BoxKernel.png

	//低通高斯滤波
	//GaussianBlur(src, dst, Size(5, 5), 1.5);  //(input, output, Size(kernelSize, kernelSize), sigma)  //GaussianBlur.png

	//拉普拉斯锐化图像
	mm.myLaplacian(src, dst);

	
	

	

	cv::namedWindow("src", cv::WINDOW_NORMAL);
	cv::imshow("src", src);

	cv::namedWindow("dst", cv::WINDOW_NORMAL);
	//cv::imshow("bitPlans", bitPlanes[1]);
	cv::imshow("dst", dst);
	cv::waitKey(0);
}

