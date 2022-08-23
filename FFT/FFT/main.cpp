#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include "fft_ifft.h"
#include <math.h>

#define height  512  
#define width   512 
#define LOW_PASS	0	//�Ƿ�Ϊ��ͨ
#define DEGREE	0		//�˲��̶�
typedef unsigned char  BYTE;    // ����BYTE���ͣ�ռ1���ֽ�  
int main(void)
{
	FILE *fp = NULL;

	//	BYTE Pic[height][width];
	BYTE *ptr;

	BYTE **Pic = new BYTE *[height];
	for (int i = 0; i != height; ++i)
	{
		Pic[i] = new BYTE[width];
	}

	int i, j;
	double max = 0;
	double min = 255;
	COMPLEX *td = NULL;
	COMPLEX *fd = NULL;
	//COMPLEX td[height*width];
	//COMPLEX fd[height*width];
	td = (COMPLEX*)malloc(height*width*sizeof(COMPLEX));
	if (td == NULL)
		return -1;
	fd = (COMPLEX*)malloc(height*width*sizeof(COMPLEX));
	if (fd == NULL)
		return -1;

	fp = fopen("weiminglake512x512.raw", "rb");
	ptr = (BYTE*)malloc(width * height * sizeof(BYTE));//�����ڴ�
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fread(ptr, 1, 1, fp);
			Pic[i][j] = *ptr;  // ��ͼ�����뵽2ά������,��ɾ�����ʽ 
			td[i * width + j].re = *ptr;
			td[i * width + j].im = 0.0;
			ptr++;
		}
	}
	fclose(fp);

	FFT2(td, height, width, fd);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			double temp = sqrt((fd[i * width + j].re / (height*width)) * (fd[i * width + j].re / (height*width)) +
				(fd[i * width + j].im / (height*width)) * (fd[i * width + j].im / (height*width)));
			if (temp > max)
				max = temp;
			if (temp < min)
				min = temp;
		}
	}
	//��ʾƵ��
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			double temp = sqrt((fd[i * width + j].re / (height*width)) * (fd[i * width + j].re / (height*width)) +
				(fd[i * width + j].im / (height*width)) * (fd[i * width + j].im / (height*width)));
			temp = (temp - min) * 25500.0 / (max - min);
			Pic[i][j] = (unsigned char)temp;
			//printf("%f\t", temp);
		}
	}
	//Ƶ�׸���λ��
	//���������û�λ��
	for (i = 0; i < height / 2;i++)
	{
		for (j = 0; j < width / 2; j++)
		{
			unsigned char t = Pic[i][j];
			Pic[i][j] = Pic[height/2 + i][width/2 + j];
			Pic[height / 2 + i][width / 2 + j] = t;
		}
	}
	//һ�������û�λ��
	for (i = 0; i < height / 2; i++)
	{
		for (j = width/2; j < width; j++)
		{
			unsigned char t = Pic[i][j];
			Pic[i][j] = Pic[height / 2 + i][j - width / 2];
			Pic[height / 2 + i][j - width / 2] = t;
		}
	}
	//����Ƶ��ͼ
	fp = fopen("pinpu.raw", "wb");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fwrite(&Pic[i][j], 1, 1, fp);
		}
	}
	fclose(fp);

	//��Ƶ�׽��д���
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if (LOW_PASS == 1){		//��ͨ���˵���Ƶ��
				if (((i<DEGREE) && (j<DEGREE)) || ((i>(width - DEGREE)) && (j<DEGREE)) ||
					((i<DEGREE) && (j>(height - DEGREE))) || ((i>(width - DEGREE)) && (j>(height - DEGREE))))
				{

				}
				else
				{
					fd[i * width + j].re = 0;
					fd[i * width + j].im = 0;
				}
			}
			else{					//��ͨ���˵���Ƶ�����ĸ�����0
				if (((i<DEGREE) && (j<DEGREE)) || ((i>(width - DEGREE)) && (j<DEGREE)) ||
					((i<DEGREE) && (j>(height - DEGREE))) || ((i>(width - DEGREE)) && (j>(height - DEGREE))))
				{
					if (((i<1) && (j<1)) || ((i>(width - 1)) && (j<1)) ||
						((i<1) && (j>(height - 1))) || ((i>(width - 1)) && (j>(height - 1))))
					{

					}
					else
					{
						fd[i * width + j].re = 0;
						fd[i * width + j].im = 0;
					}

				}
			}
		}
	}

	//���洦��Ƶ��ͼ
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			double temp = sqrt((fd[i * width + j].re / (height*width)) * (fd[i * width + j].re / (height*width)) +
				(fd[i * width + j].im / (height*width)) * (fd[i * width + j].im / (height*width)));
			temp = (temp - min) * 25500.0 / (max - min);
			Pic[i][j] = (unsigned char)temp;
			//printf("%f\t", temp);
		}
	}
	//Ƶ�׸���λ��
	//���������û�λ��
	for (i = 0; i < height / 2; i++)
	{
		for (j = 0; j < width / 2; j++)
		{
			unsigned char t = Pic[i][j];
			Pic[i][j] = Pic[height / 2 + i][width / 2 + j];
			Pic[height / 2 + i][width / 2 + j] = t;
		}
	}
	//һ�������û�λ��
	for (i = 0; i < height / 2; i++)
	{
		for (j = width / 2; j < width; j++)
		{
			unsigned char t = Pic[i][j];
			Pic[i][j] = Pic[height / 2 + i][j - width / 2];
			Pic[height / 2 + i][j - width / 2] = t;
		}
	}
	fp = fopen("p_pinpu.raw", "wb");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fwrite(&Pic[i][j], 1, 1, fp);
		}
	}
	fclose(fp);
	IFFT2(td,height, width, fd);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			double temp = sqrt((td[i * width + j].re) * (td[i * width + j].re) +
				(fd[i * width + j].im) * (fd[i * width + j].im));
			Pic[i][j] = (unsigned char)td[i * width + j].re;
			Pic[i][j] = (unsigned char)temp;
			//printf("%f\t", temp);
		}
	}

	fp = fopen("processed.raw", "wb");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fwrite(&Pic[i][j], 1, 1, fp);
		}
	}
	fclose(fp);
	system("pause");
	return 0;
}
