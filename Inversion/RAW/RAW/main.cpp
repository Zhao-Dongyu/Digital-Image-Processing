#include <stdio.h>  
#include <stdlib.h>  
//#include <string.h>  

#define height  600  
#define width   800*3 

typedef unsigned char  BYTE;    // 定义BYTE类型，占1个字节  
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
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));//创建内存
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			Pic[i][j] = *ptr;  // 把图像输入到2维数组中,变成矩阵型式  
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

	// 输入源路径并打开raw图像文件  
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

	// 分配内存并将图像读到二维数组中        
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			B[i][j] = *ptr;  // 把图像输入到2维数组中,变成矩阵型式  
			printf("%d  ", B[i][j]);
			ptr++;
		}
	}
	fclose(fp);

	// 这里可以对二维数组中的图像数据进行处理  

	// 将处理后的图像数据输出至文件  
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