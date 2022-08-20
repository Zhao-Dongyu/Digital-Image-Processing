#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

using namespace std;
using namespace cv;

int main() {   
	Mat src;
	int height;
	int width;
	int i;
	int j;
	//载入图片
	src = imread("weiminglake_huidu.jpg");
	if (!src.data)
	{
		cout << "Could not open or find image." << endl;
		return -1;
	}
	//获取图像信息
	height = src.rows;
	width = src.cols* src.channels();   // 列项要乘通道数
										//创建窗口
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	//显示图片
	imshow("src", src);
	//图像反转
	for (i = 0; i< height; i++)
	{
		for (j = 0; j< width; j++)
		{
			src.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);   // 每一个像素反转
		}
	}
	//显示图片
	imshow("dst", src);
	waitKey(0);
	return 0;
}