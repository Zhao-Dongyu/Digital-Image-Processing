#include <stdio.h>
#include "jpeg_encoder.h"

//-------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	const char* inputFileName = "weiminglake.bmp";
	JpegEncoder encoder;
	//输入的文件必须是24bit的bmp文件，尺寸必须是8的倍数
	if(!encoder.readFromBMP(inputFileName))
	{
		return 1;
	}
	printf("read BMP success!\r\n");
	//第二个参数在1~199之间，代表文件压缩程度，数字越大，压缩后的文件体积越小
	if(!encoder.encodeToJPG("out.jpg", 50))
	{
		return 1;
	}
	return 0;
}
