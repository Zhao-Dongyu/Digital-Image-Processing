#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>
#include <string.h>  
#include "filt.h"

int main(void)
{
	FILE *fp = NULL;
	BYTE *input = NULL;
	BYTE *output = NULL;

	input = (BYTE*)malloc(width * height * sizeof(BYTE));
	output = (BYTE*)malloc(width * height * sizeof(BYTE));

	fp = fopen("Fig0510(a)(ckt-board-saltpep-prob.pt05).raw", "rb");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fread(input, 1, 1, fp);
			input++;
		}
	}
	input -= height * width;
	fclose(fp);
	
	//FILT33MEAN(input, output, height, width);
	//FILT33GMV(input, output, height, width);
	FILT_MIDDLE(input, output, height, width);
	//±£´æÎÄ¼þ
	fp = fopen("output.raw", "wb");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fwrite(output, 1, 1, fp);
			output++;
		}
	}
	output -= height * width;
	fclose(fp);
	free(input);
	free(output);
	//getchar();
	return 0;
}
