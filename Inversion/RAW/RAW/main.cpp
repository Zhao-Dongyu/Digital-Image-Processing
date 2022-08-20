#include <stdio.h>  
#include <stdlib.h>  
//#include <string.h>  

#define height  600  
#define width   800*3 

typedef unsigned char  BYTE;    // ����BYTE���ͣ�ռ1���ֽ�  
int main(void)
{

	int a = 100;
	unsigned int b = -100;
	if (a > b)
		printf("a>b");
	else
		printf("a<b");
	system("pause");
	FILE *fp = NULL;

//	BYTE Pic[height][width];
	BYTE *ptr;

	BYTE **Pic = new BYTE *[height];
	for (int i = 0; i != height; ++i)
	{
		Pic[i] = new BYTE[width];
	}

	int i, j;
	char temp;
	fp = fopen("weiminglake_color.raw", "rb");       
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));//�����ڴ�
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			Pic[i][j] = *ptr;  // ��ͼ�����뵽2ά������,��ɾ�����ʽ  
			ptr++;
		}
	}
	fclose(fp);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j+=3)
		{ 
			temp = Pic[i][j];
			Pic[i][j] = Pic[i][j+2];
			Pic[i][j+2] = temp;

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

/*
int main(void)
{
	FILE *fp = NULL;

	BYTE B[height][width];
	BYTE *ptr;

	char path[256];
	char outpath[256];

	int i, j;

	// ����Դ·������rawͼ���ļ�  
	printf("Input the raw image path: ");
	scanf("%s", path);
	if ((fp = fopen(path, "rb")) == NULL)
	{
		printf("can not open the raw image ");
		return 1;
	}
	else
	{
		printf("read OK");
	}

	// �����ڴ沢��ͼ�������ά������        
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			B[i][j] = *ptr;  // ��ͼ�����뵽2ά������,��ɾ�����ʽ  
			printf("%d  ", B[i][j]);
			ptr++;
		}
	}
	fclose(fp);

	// ������ԶԶ�ά�����е�ͼ�����ݽ��д���  

	// ��������ͼ������������ļ�  
	printf("Input the raw_image path for save: ");
	scanf("%s", outpath);
	if ((fp = fopen(outpath, "wb")) == NULL)
	{
		printf("can not create the raw_image : %s\n", outpath);
		system("pause");
		return 1;
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fwrite(&B[i][j], 1, 1, fp);
		}
	}
	fclose(fp);
	return 0;
}
*/