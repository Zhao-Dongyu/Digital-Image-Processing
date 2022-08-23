#include <stdio.h>  
#include <stdlib.h>  
#include <memory.h>

#define height  600  
#define width   800

typedef unsigned char  BYTE;    // 定义BYTE类型，占1个字节 

int main(void)
{
	FILE *fp = NULL;
	//BYTE Pic[height][width];
	BYTE *ptr;

	BYTE **Pic = new BYTE *[height];
	for (int i = 0; i != height; ++i)
	{
		Pic[i] = new BYTE[width];
	}

	fp = fopen("weiminglake_huidu.raw", "rb");       
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

	int hist[256];
	float  fpHist[256];
	float eqHistTemp[256];
	int eqHist[256];
	int size = height *width;
	int i, j;

	memset(&hist, 0x00, sizeof(int) * 256);
	memset(&fpHist, 0x00, sizeof(float) * 256);
	memset(&eqHistTemp, 0x00, sizeof(float) * 256);
	for (i = 0; i < height; i++) //计算差分矩阵直方图  直方图  统计每个灰度级像素点的个数
	{
		for (j = 0; j < width; j++)
		{
			unsigned char GrayIndex = Pic[i][j];
			hist[GrayIndex] ++;
		}
	}
//	for (i = 0; i < 256; i++)
//	{
//		printf("hist[%d] = %d\t",i,hist[i]);
//	}
//	system("pause");
	for (i = 0; i< 256; i++)   // 计算灰度分布密度
	{
		fpHist[i] = (float)hist[i] / (float)size;
	}
	for (i = 0; i< 256; i++)   // 计算累计直方图分布
	{
		if (i == 0)
		{
			eqHistTemp[i] = fpHist[i];
		}
		else
		{
			eqHistTemp[i] = eqHistTemp[i - 1] + fpHist[i];
		}
	}

	//累计分布取整，保存计算出来的灰度映射关系
	for (i = 0; i< 256; i++)
	{
		eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
	}
	for (i = 0; i < height; i++) //进行灰度映射 均衡化
	{
		for (j = 0; j < width; j++)
		{
			unsigned char GrayIndex = Pic[i][j];
			Pic[i][j] = eqHist[GrayIndex];
		}
	}
	fp = fopen("output.raw", "wb");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fwrite(&Pic[i][j], 1, 1, fp);
		}
	}
	fclose(fp);
	return 0;
}
