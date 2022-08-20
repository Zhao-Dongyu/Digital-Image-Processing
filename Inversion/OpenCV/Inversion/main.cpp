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
	//����ͼƬ
	src = imread("weiminglake_huidu.jpg");
	if (!src.data)
	{
		cout << "Could not open or find image." << endl;
		return -1;
	}
	//��ȡͼ����Ϣ
	height = src.rows;
	width = src.cols* src.channels();   // ����Ҫ��ͨ����
										//��������
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	//��ʾͼƬ
	imshow("src", src);
	//ͼ��ת
	for (i = 0; i< height; i++)
	{
		for (j = 0; j< width; j++)
		{
			src.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);   // ÿһ�����ط�ת
		}
	}
	//��ʾͼƬ
	imshow("dst", src);
	waitKey(0);
	return 0;
}