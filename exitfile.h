#pragma once
#pragma pack(1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void exitfile(img_t *img)
{
	int i;
	//we verify if we have an image to close
	if (!img->mat_c && !img->mat_i) {
		printf("No image loaded\n");
		exit(0);
	}
	/*here we free them the same, the only difference is the type 
	of matrix we have*/
	if(img->mat_c) {
		for(i = 0; i < img->height; i++)
			free(img->mat_c[i]);
		free(img->mat_c);
	}
	if(img->mat_i) {
		for(i = 0; i < img->height; i++) 
			free(img->mat_i[i]);
		free(img->mat_i);
	}
	//we close the program
	exit(0);
}
