#pragma once
#pragma pack(1)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

void crop(img_t *img)
{
	int i, j;
	//we verify if we have an image to crop
	if (!img->mat_c && !img->mat_i) {
		printf("No image loaded\n");
		return ;
	}
	/*we verify what type of image we have, bcs for grayscale we have a simple
	unisgned char matrix, but for the color one we have a struct matrix
	the way they work is pretty similar, we alloc a new matrix with the selected
	coordinates, we copy the info from the original photo, we free the original photo,
	we put the new image in at the old address, and we reset x1,x2,y1,y2 to the corners*/
	if(img->type[1] == '2' || img->type[1] == '5') {
		int m = img->x2 - img->x1, n = img->y2 - img->y1;
		unsigned char **tmp_mat = (unsigned char **) malloc(n * sizeof(unsigned char *));
		for(i = 0; i < n; i++) {
			tmp_mat[i] = (unsigned char *) malloc(m * sizeof(unsigned char));
			if(!tmp_mat[i]) {
				for(; i > 0; i--)
					free(tmp_mat[i]);
				free(tmp_mat);
				return;
			}
		}

		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++)
				tmp_mat[i][j] = img->mat_i[i + img->y1][j + img->x1];
		}
		for(i = 0; i < img->height; i++)
			free(img->mat_i[i]);
		free(img->mat_i);
		img->mat_i = tmp_mat;
		img->width = m;
		img->height = n;
		img->x1 = 0;
		img->x2 = m;
		img->y1 = 0;
		img->y2 = n;
	}
	else {
		int m = img->x2 - img->x1, n = img->y2 - img->y1;
		pixelcol_t **tmp_mat = (pixelcol_t **) malloc(n * sizeof(pixelcol_t *));
		if(!tmp_mat) {
			free(tmp_mat);
			return;
		}
		for(i = 0; i < n; i++) {
			tmp_mat[i] = (pixelcol_t *) malloc(m * sizeof(pixelcol_t));
			if(!tmp_mat[i]) {
				for(; i > 0; i--)
					free(tmp_mat[i]);
				free(tmp_mat);
				return;
			}
		}
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				tmp_mat[i][j].R = img->mat_c[i + img->y1][j + img->x1].R;
				tmp_mat[i][j].G = img->mat_c[i + img->y1][j + img->x1].G;
				tmp_mat[i][j].B = img->mat_c[i + img->y1][j + img->x1].B;
			}
		}
		for(i = 0; i < img->height; i++)
			free(img->mat_c[i]);
		free(img->mat_c);
		img->mat_c = tmp_mat;
		img->width = m;
		img->height = n;
		img->x1 = 0;
		img->x2 = m;
		img->y1 = 0;
		img->y2 = n;
	}
	printf("Image cropped\n");
}
