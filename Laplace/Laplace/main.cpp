#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>
#include <string.h>  

constexpr auto height = 400  ;
constexpr auto width = 400 ;

typedef unsigned char  BYTE;    // 定义BYTE类型，占1个字节 

int main(void)
{
	FILE *fp = NULL;
	BYTE *input = NULL;
	BYTE *output = NULL;

	int temp;
	int ia1,ja1,im1,jm1;

	input  = (BYTE*)malloc(width * height * sizeof(BYTE));
	output = (BYTE*)malloc(width * height * sizeof(BYTE));


	fp = fopen("blurry_moon.raw", "rb");
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			fread(input, 1, 1, fp);
			input++;
		}
	}
	input -= height * width;
	fclose(fp);

	//拉普拉斯
	//		 0		+1		 0
	//		+1		-4		+1
	//		 0		+1		 0
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ia1 = (i + 1 > width - 1) ? width - 1 : i + 1;
			ja1 = (j + 1 > width - 1) ? width - 1 : j + 1;
			im1 = (i - 1 < 0) ? 0 : i - 1;
			jm1 = (j - 1 < 0) ? 0 : j - 1;
			temp = input[im1 * width + j] + input[i * width + jm1] - 4 * input[i * width + j]
				 + input[i * width + ja1] + input[ia1 * width + j];
			temp = -temp + input[i * width + j];
			if (temp < 0)temp = 0;
			output[i * width + j] = (unsigned char)temp;
		}
	}


	//保存文件
	fp = fopen("output.raw", "wb");
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			fwrite(output, 1, 1, fp);
			output++;
		}
	}
	output -= height * width;
	fclose(fp);
	free(input);
	free(output);
	return 0;
}
