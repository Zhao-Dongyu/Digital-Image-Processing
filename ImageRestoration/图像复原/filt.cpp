#include "filt.h"
#include "math.h"
#include <string.h> 
#include <stdio.h>  
/*
3x3平均值滤波
*/
void FILT33MEAN(void *I_image, void *O_image, int size_x, int size_y)
{
	int i, j, ia1, im1, ja1, jm1;
	float mean_value;
	BYTE *ptr1, *ptr2;

	ptr1 = (BYTE *)I_image;
	ptr2 = (BYTE *)O_image;

	for (i = 0; i < size_x; i++)
	{
		for (j = 0; j < size_y; j++)
		{
			ia1 = (i + 1 > size_x - 1) ? size_x - 1 : i + 1;//get i+1
			ja1 = (j + 1 > size_y - 1) ? size_y - 1 : j + 1;//get j+1
			im1 = (i - 1 < 0) ? 0 : i - 1;//get i-1
			jm1 = (j - 1 < 0) ? 0 : j - 1;//get j-1
			mean_value =ptr1[im1 * size_y + jm1] + ptr1[im1 * size_y + j] + ptr1[im1 * size_y + ja1]
				+ ptr1[i * size_y + jm1] + ptr1[i * size_y + ja1]
				+ ptr1[ia1 * size_y + jm1] + ptr1[ia1 * size_y + j] + ptr1[ia1 * size_y + ja1];
			mean_value = mean_value / 8.0;
			ptr2[i*size_y + j] = (BYTE)mean_value;
		}
	}
}

/*
3x3几何均值滤波
*/
void FILT33GMV(void *I_image, void *O_image, int size_x, int size_y)
{
	int i, j, ia1, im1, ja1, jm1;
	double gmv_value = 1;
	BYTE *ptr1, *ptr2;

	ptr1 = (BYTE *)I_image;
	ptr2 = (BYTE *)O_image;

	for (i = 0; i < size_x; i++)
	{
		for (j = 0; j < size_y; j++)
		{
			ia1 = (i + 1 > size_x - 1) ? size_x - 1 : i + 1;//get i+1
			ja1 = (j + 1 > size_y - 1) ? size_y - 1 : j + 1;//get j+1
			im1 = (i - 1 < 0) ? 1 : i - 1;//get i-1
			jm1 = (j - 1 < 0) ? 1 : j - 1;//get j-1
			gmv_value *= ptr1[im1 * size_y + jm1] / 255.0;
			gmv_value *= ptr1[im1 * size_y + j] / 255.0;
			gmv_value *= ptr1[im1 * size_y + ja1] / 255.0;
			gmv_value *= ptr1[i * size_y + jm1] / 255.0;
			gmv_value *= ptr1[i * size_y + ja1] / 255.0;
			gmv_value *= ptr1[ia1 * size_y + jm1] / 255.0;
			gmv_value *= ptr1[ia1 * size_y + j] / 255.0;
			gmv_value *= ptr1[ia1 * size_y + ja1] / 255.0;
			gmv_value = pow(gmv_value, 1.0 / 8);
			ptr2[i*size_y + j] = (BYTE)(gmv_value*255);
			gmv_value = 1;
			//gmv_value = ptr1[im1 * size_y + jm1] * ptr1[im1 * size_y + j] * ptr1[im1 * size_y + ja1]
				//* ptr1[i * size_y + jm1] * ptr1[i * size_y + ja1]
				//* ptr1[ia1 * size_y + jm1] * ptr1[ia1 * size_y + j] * ptr1[ia1 * size_y + ja1] / 255.0/255.0/255.0/255.0/255.0/255.0/255.0/255.0;
			//printf("%d\t",gmv_value);

		}
	}
	//printf("%f\t", pow(256,1.0/8));
}

/*
中值滤波
*/
void FILT_MIDDLE(void *I_image, void *O_image, int size_x, int size_y)
{
	int i, j, ia1, im1, ja1, jm1, temp;
	int ii, jj;
	BYTE *ptr1, *ptr2;
	BYTE mask[9];

	ptr1 = (BYTE *)I_image;
	ptr2 = (BYTE *)O_image;

	for (i = 0; i < size_x; i++)
	{
		for (j = 0; j < size_y; j++)
		{
			ia1 = (i + 1 > size_x - 1) ? size_x - 1 : i + 1;//get i+1
			ja1 = (j + 1 > size_y - 1) ? size_y - 1 : j + 1;//get j+1
			im1 = (i - 1 < 0) ? 0 : i - 1;//get i-1
			jm1 = (j - 1 < 0) ? 0 : j - 1;//get j-1
			mask[0] = ptr1[im1 * size_y + jm1];
			mask[1] = ptr1[im1 * size_y + j];
			mask[2] = ptr1[im1 * size_y + ja1];
			mask[3] = ptr1[i * size_y + jm1];
			mask[4] = ptr1[i * size_y + j];
			mask[5] = ptr1[i * size_y + ja1];
			mask[6] = ptr1[ia1 * size_y + jm1];
			mask[7] = ptr1[ia1 * size_y + j];
			mask[8] = ptr1[ia1 * size_y + ja1];
			for (ii = 0; ii < 8; ii++){
				for (jj = 0; jj < 8 - ii; jj++){
					if (mask[jj] > mask[jj + 1]){
						temp = mask[jj];
						mask[jj] = mask[jj + 1];
						mask[jj + 1] = temp;
					}
				}
			}
			ptr2[i*size_y + j] = mask[4];
		}
	}
}