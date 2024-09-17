#pragma once
#pragma pack(1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void savefile(img_t *img, char *filename, char *filetype)
{
	int i, j;
	//we verify if we have an image to save
	if (!img->mat_c && !img->mat_i) {
		printf("No image loaded\n");
		return;
	}
	//we open the file
	FILE *out = fopen(filename, "wt");
	/*we verify what type of file the user wants to the photo as.
	also, we have for each type of file, two types of images:
	color and non-color*/
	if (filetype && (strcmp(filetype, "ascii")) == 0) {
		if(img->mat_i)  {
			fprintf(out,"P2\n%d %d\n%d\n", img->width, img->height, img->max);
			for(i = 0; i < img->height; i++) {
				for(j = 0; j < img->width; j++)
					fprintf(out, "%hhu ", img->mat_i[i][j]);
			fprintf(out, "\n");
			}
		} else {
			fprintf(out,"P3\n%d %d\n%d\n", img->width, img->height, img->max);
			for(i = 0; i < img->height; i++) {
				for(j = 0; j < img->width; j++) {
					fprintf(out, "%hhu ",img->mat_c[i][j].R);
					fprintf(out, "%hhu ",img->mat_c[i][j].G);
					fprintf(out, "%hhu ",img->mat_c[i][j].B);
					}
			fprintf(out, "\n");
			}
		}
	} else {
		/*here we have the binary file, so we have to close the write text mode
		and to open it  an append binary*/
		if(img->mat_i) {
			fprintf(out,"P5\n%d %d\n%d\n", img->width, img->height, img->max);
			fclose(out);
			out = fopen(filename, "ab");
			for(i = 0; i < img->height; i++) {
				for(j = 0; j < img->width; j++) {
					fwrite(&img->mat_i[i][j], sizeof(unsigned char), 1, out);
				}
			}
		} else {
			fprintf(out,"P6\n%d %d\n%d\n", img->width, img->height, img->max);
			fclose(out);
			out = fopen(filename, "ab");
			for(i = 0; i < img->height; i++) {
				for(j = 0; j < img->width; j++) {
					fwrite(&img->mat_c[i][j].R, sizeof(unsigned char), 1, out);
					fwrite(&img->mat_c[i][j].G, sizeof(unsigned char), 1, out);
					fwrite(&img->mat_c[i][j].B, sizeof(unsigned char), 1, out);
				}
			}
		}

	}
	//we close the file that we opened
	fclose(out);
	fprintf(stdout, "Saved %s\n", filename);
}