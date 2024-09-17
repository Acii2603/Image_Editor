#pragma once
#pragma pack(1)
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "struct.h"

void newpixel(img_t *img, double effect[3][3], double r)
{
	int a1 = img->x1, a2 = img->x2, b1 = img->y1, b2 = img->y2, i, j, k, l;
	double aux[3] ={0};
	if(a1 == 0)
		a1++;
	if(b1 == 0)
		b1++;
	if(a2 == img->width)
		a2--;
	if(b2 == img->height)
		b2--;
	pixelcol_t **tmp = (pixelcol_t **) malloc((b2 - b1) * sizeof(pixelcol_t*));
	for(i = 0; i < b2 - b1; i++)
		tmp[i] = (pixelcol_t *) malloc((a2 - a1) * sizeof(pixelcol_t));
	
	for(i = b1; i < b2; i++) {
		for(j = a1; j < a2; j++) {
			aux[0] = 0;
			aux[1] = 0;
			aux[2] = 0;
			for(k = -1; k <= 1; k++) {
				for(l = -1; l <= 1; l++) {
					double a =img->mat_c[i + k][j + l].R * 1.00;
					double g =img->mat_c[i + k][j + l].G * 1.00;
					double b =img->mat_c[i + k][j + l].B * 1.00;

					aux[0] += a * effect[k + 1][l + 1] / r;
					aux[1] += g * effect[k + 1][l + 1] / r;
					aux[2] += b * effect[k + 1][l + 1] /r;
				}
			}
			for(k = 0; k < 3; k++)
				aux[k] = round(aux[k]);

			for(k = 0; k < 3; k++) {
				if(aux[k] < 0)
					aux[k] = 0;
				if(aux[k] > img->max)
					aux[k] = img->max;
			}

			tmp[i - b1][j - a1].R = (unsigned char)aux[0];
			tmp[i - b1][j - a1].G = (unsigned char)aux[1];
			tmp[i - b1][j - a1].B = (unsigned char)aux[2];
		}
	}
	for(i = b1; i < b2; i++) {
		for(j = a1; j < a2; j++) {
			img->mat_c[i][j].R = tmp[i - b1][j - a1].R;
			img->mat_c[i][j].G = tmp[i - b1][j - a1].G;
			img->mat_c[i][j].B = tmp[i - b1][j - a1].B;
		}
	}
	for(i = 0; i < b2 - b1; i++)
		free(tmp[i]);
	free(tmp);
}

void apply(img_t *img, char *args)
{
	if(img->mat_i) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	double r;
	double edge[3][3] = {{-1.0, -1.0, -1.0}, {-1.0, 8.0, -1.0}, {-1.0, -1.0, -1.0}};
	double sharp[3][3] = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};
	double box[3][3] = {{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}};
	double gauss[3][3] = {{1.0, 2.0, 1.0}, {2.0, 4.0, 2.0}, {1.0, 2.0, 1.0}};
	if(strcmp(args, "EDGE") == 0) {
		r = 1;
		newpixel(img, edge, r);
	}
	else if(strcmp(args, "SHARPEN") == 0) {
		r = 1;
		newpixel(img, sharp, r);
	}
	else if(strcmp(args, "BLUR") == 0) {
		r = 9;
		newpixel(img, box, r);
	}
	else if(strcmp(args, "GAUSSIAN_BLUR") == 0) {
		r = 16;
		newpixel(img, gauss, r);

	}
	else {
		printf("APPLY parameter invalid\n");
		return;
	}
	printf("APPLY %s done\n", args);
	return;
}
