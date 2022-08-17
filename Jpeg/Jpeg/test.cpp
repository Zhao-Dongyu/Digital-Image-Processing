#include <stdio.h>
#include "jpeg_encoder.h"

//-------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	const char* inputFileName = "weiminglake.bmp";
	JpegEncoder encoder;
	//������ļ�������24bit��bmp�ļ����ߴ������8�ı���
	if(!encoder.readFromBMP(inputFileName))
	{
		return 1;
	}
	printf("read BMP success!\r\n");
	//�ڶ���������1~199֮�䣬�����ļ�ѹ���̶ȣ�����Խ��ѹ������ļ����ԽС
	if(!encoder.encodeToJPG("out.jpg", 50))
	{
		return 1;
	}
	return 0;
}
