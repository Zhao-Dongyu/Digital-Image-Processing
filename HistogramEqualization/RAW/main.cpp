#include <stdio.h>  
#include <stdlib.h>  
#include <memory.h>

#define height  600  
#define width   800

typedef unsigned char  BYTE;    // ����BYTE���ͣ�ռ1���ֽ� 

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
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));//�����ڴ�
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			Pic[i][j] = *ptr;  // ��ͼ�����뵽2ά������,��ɾ�����ʽ  
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
	for (i = 0; i < height; i++) //�����־���ֱ��ͼ  ֱ��ͼ  ͳ��ÿ���Ҷȼ����ص�ĸ���
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
	for (i = 0; i< 256; i++)   // ����Ҷȷֲ��ܶ�
	{
		fpHist[i] = (float)hist[i] / (float)size;
	}
	for (i = 0; i< 256; i++)   // �����ۼ�ֱ��ͼ�ֲ�
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

	//�ۼƷֲ�ȡ���������������ĻҶ�ӳ���ϵ
	for (i = 0; i< 256; i++)
	{
		eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
	}
	for (i = 0; i < height; i++) //���лҶ�ӳ�� ���⻯
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
