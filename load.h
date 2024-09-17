#pragma once
#pragma pack(1)
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void loadfile(img_t *img, char inputfilename[100])
{
	//here we open the file to read the info we need
	int i, j;
	FILE *in = fopen(inputfilename, "rb");
	//if the file doesn't exist, we close everything
	if (in == NULL) {
		if(img->mat_c) {
			for(i = 0; i < img->height; i++)
				free(img->mat_c[i]);
			free(img->mat_c);
			img->mat_c = NULL;
		}
		if(img->mat_i) {
			for(i = 0; i < img->height; i++) 
				free(img->mat_i[i]);
			free(img->mat_i);
			img->mat_i = NULL;
		}
		fprintf(stdout, "Failed to load %s\n", inputfilename);
		return;
	}
	//if we already have an color matrix, we free it from the memory
	if(img->mat_c) {
		for(i = 0; i < img->height; i++)
			free(img->mat_c[i]);
		free(img->mat_c);
		img->mat_c = NULL;
	}
	//if we already have an black-white matrix, we free it from the memory
	if(img->mat_i) {
		for(i = 0; i < img->height; i++) 
			free(img->mat_i[i]);
		free(img->mat_i);
		img->mat_i = NULL;
	}
	fscanf(in, "%s", (img->type));
	//we verify that the file we opened has the right type
	if(img->type[0] != 'P' || img->type[1] > '6') {
		fprintf(stdout, "Failed to load %s\n", inputfilename);
		fclose(in);
		return;
	}
	//we read the size of the image and also the max value of the pixels
	fscanf(in, "%d", &(img->width));
	fscanf(in, "%d", &(img->height));
	fscanf(in, "%d\n", &(img->max));
	//here we alloc the matrices depending on type and read them from the file
	if(img->type[1] == '2') {
		int m = img->width, n = img->height;
		unsigned char **tmp_mat = (unsigned char **) malloc(n * sizeof(unsigned char *));
		if(!tmp_mat) {
			fprintf(stdout, "Failed to load %s\n", inputfilename);
			free(tmp_mat);
			fclose(in);
			return;
		}
		for(i = 0; i < n; i++) {
			tmp_mat[i] = (unsigned char *) malloc(m * sizeof(unsigned char));
			if(!tmp_mat[i]) {
				fprintf(stdout, "Failed to load %s\n", inputfilename);
				for(; i > 0; i--)
					free(tmp_mat[i]);
				free(tmp_mat);
				return;
			}
		}
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				fscanf(in,"%hhu",&tmp_mat[i][j]);
			}
		}
		img->mat_i = tmp_mat;
	}
	if(img->type[1] == '3') {
		int m = img->width, n = img->height;
		pixelcol_t **tmp_mat = (pixelcol_t **) malloc(n * sizeof(pixelcol_t *));
		if(!tmp_mat) {
			fprintf(stdout, "Failed to load %s\n", inputfilename);
			free(tmp_mat);
			fclose(in);
			return;
		}
		for(i = 0; i < n; i++) {
			tmp_mat[i] = (pixelcol_t *) malloc(m * sizeof(pixelcol_t));
			if(!tmp_mat[i]) {
				fprintf(stdout, "Failed to load %s\n", inputfilename);
				for(; i > 0; i--)
					free(tmp_mat[i]);
				free(tmp_mat);
				fclose(in);
				return;
			}
		}

		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				fscanf(in, "%hhu", &tmp_mat[i][j].R);
				fscanf(in, "%hhu", &tmp_mat[i][j].G);
				fscanf(in, "%hhu", &tmp_mat[i][j].B);
			}

		}
		img->mat_c = tmp_mat;
	}
	//what's above 5 we have binary file, so we use fread
	if(img->type[1] == '5') {
		int m = img->width, n = img->height;
		unsigned char **tmp_mat = (unsigned char **) malloc(n * sizeof(unsigned char *));
		if(!tmp_mat) {
			fprintf(stdout, "Failed to load %s\n", inputfilename);
			free(tmp_mat);
			return;
		}
		for(i = 0; i < n; i++) {
			tmp_mat[i] = (unsigned char *) 
						 malloc(m * sizeof(unsigned char));
			if(!tmp_mat[i]) {
				fprintf(stdout, "Failed to load %s\n", inputfilename);
				for(; i > 0; i--)
					free(tmp_mat[i]);
				free(tmp_mat);
				fclose(in);
				return;
			}
		}

		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				fread(&tmp_mat[i][j], sizeof(unsigned char), 1, in);
			}
		}
		img->mat_i = tmp_mat;
	}
	if(img->type[1] == '6') {
		int m = img->width, n = img->height;
		pixelcol_t **tmp_mat = (pixelcol_t **) malloc(n * sizeof(pixelcol_t *));
		if(!tmp_mat) {
			fprintf(stdout, "Failed to load %s\n", inputfilename);
			free(tmp_mat);
			fclose(in);
			return;
		}
		for(i = 0; i < n; i++) {
			tmp_mat[i] = (pixelcol_t *) malloc(m * sizeof(pixelcol_t));
			if(!tmp_mat[i]) {
				fprintf(stdout, "Failed to load %s\n", inputfilename);
				for(; i > 0; i--)
					free(tmp_mat[i]);
				free(tmp_mat);
				fclose(in);
				return;
			}
		}

		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				fread(&tmp_mat[i][j].R, sizeof(unsigned char), 1, in);
				fread(&tmp_mat[i][j].G, sizeof(unsigned char), 1, in);
				fread(&tmp_mat[i][j].B, sizeof(unsigned char), 1, in);
			}

		}
		img->mat_c = tmp_mat;
	}
	//we put the corners of the photo in x1, x2, y1, y2, and we close the file
	img->x1 = 0;
	img->y1 = 0;
	img->x2 = img->width;
	img->y2 = img->height;
	fclose(in);
	fprintf(stdout, "Loaded %s\n", inputfilename);
}
