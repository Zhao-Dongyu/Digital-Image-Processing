#include <stdio.h>  
#include <stdlib.h>  
#include <memory.h>

#define height  100  
#define width   100

typedef unsigned char  BYTE;    // 定义BYTE类型，占1个字节 

int main(void)
{
	FILE *fp = NULL;
	BYTE PicZoomOut[100][100];
	BYTE PicZoomIn[200][200];
	BYTE *ptr;

	BYTE **Pic = new BYTE *[height];
	for (int i = 0; i != height; ++i)
	{
		Pic[i] = new BYTE[width];
	}

	fp = fopen("100.raw", "rb");       
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));//创建内存
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			Pic[i][j] = *ptr;  // 把图像输入到2维数组中,变成矩阵型式  
			ptr++;
		}
	}
	fclose(fp);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			PicZoomIn[i * 2][j * 2] = Pic[i][j];
			PicZoomIn[i * 2 + 1][j * 2] = Pic[i][j];
			PicZoomIn[i * 2][j * 2 + 1] = Pic[i][j];
			PicZoomIn[i * 2 + 1][j * 2 + 1] = Pic[i][j];
		}
	}

	fp = fopen("output.raw", "wb");
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			fwrite(&PicZoomIn[i][j], 1, 1, fp);
		}
	}
	fclose(fp);
	return 0;
}


/*图像缩小
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define height  200
#define width   200

typedef unsigned char  BYTE;    // 定义BYTE类型，占1个字节

int main(void)
{
FILE *fp = NULL;
BYTE PicZoomOut[100][100];
BYTE PicZoomIn[400][400];
BYTE *ptr;

BYTE **Pic = new BYTE *[height];
for (int i = 0; i != height; ++i)
{
Pic[i] = new BYTE[width];
}

fp = fopen("1.raw", "rb");
ptr = (BYTE*)malloc(width * height * sizeof(BYTE));//创建内存
for (int i = 0; i < height; i++)
{
for (int j = 0; j < width; j++)
{
fread(ptr, 1, 1, fp);
Pic[i][j] = *ptr;  // 把图像输入到2维数组中,变成矩阵型式
ptr++;
}
}
fclose(fp);

for (int i = 0; i < 50; i++)
{
for (int j = 0; j < 50; j++)
{
PicZoomOut[i][j] = (Pic[i * 4][j * 4]     + Pic[i * 4 + 1][j * 4]     + Pic[i * 4 + 2][j * 4]     + Pic[i * 4 + 3][j * 4]
+ Pic[i * 4][j * 4 + 1] + Pic[i * 4 + 1][j * 4 + 1] + Pic[i * 4 + 2][j * 4 + 1] + Pic[i * 4 + 3][j * 4 + 1]
+ Pic[i * 4][j * 4 + 2] + Pic[i * 4 + 1][j * 4 + 2] + Pic[i * 4 + 2][j * 4 + 2] + Pic[i * 4 + 3][j * 4 + 2]
+ Pic[i * 4][j * 4 + 3] + Pic[i * 4 + 1][j * 4 + 3] + Pic[i * 4 + 2][j * 4 + 3] + Pic[i * 4 + 3][j * 4 + 3])/16;
}
}

fp = fopen("output.raw", "wb");
for (int i = 0; i < 50; i++)
{
for (int j = 0; j < 50; j++)
{
fwrite(&PicZoomOut[i][j], 1, 1, fp);
}
}
fclose(fp);
return 0;
}

*/