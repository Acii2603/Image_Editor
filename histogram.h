#pragma once
#pragma pack(1)
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "struct.h"

int number(char s[100])
{
	char cpy[100];
	int i = 0, rez = 0;
	strcpy(cpy, s);
	cpy[strlen(cpy)] = '\n';
	while(cpy[i] != '\n') {
		rez = rez * 10 + (cpy[i] - '0');
		i++;
	}
	return rez;
}
/* here I tried my best, but it didn't work TT
what I tried is that I alloced 2 frequency arrays
in the first one I put the frequency of all the values and
in the second one I added the 256/bin values to make the frequency
after bin */
void histogram(img_t *img, char *x, char *y)
{
	if(x[0] == '-' || y[0] == '-') {
		printf("Invalid set of parameters\n");
		return;
	}
	if(img->mat_c) {
		printf("Black and white image needed\n");
		return;
	}
	int i, j, bin;
	int *freq1 = (int *) calloc(img->max + 1, sizeof(int));
	if(!freq1) {
		free(freq1);
		return;
	}
	for(i = 0; i < img->height; i++) {
		for(j = 0; j < img->width; j++)
			freq1[img->mat_i[i][j]]++;
	}
	bin = number(y);
	int *freq2 = (int *) calloc(bin, sizeof(int));
	for(i = 0; i < 255; i++) {
		freq2[j] += freq1[i];
		if(i % (int)(256 / bin) == 0)
			j++;
	}
	int max = 0;
	for(i = 0; i < bin; i++)
		if(freq2[i] > max)
			max = freq2[i];
	int nstars, nmaxstars;
	nmaxstars = number(x);
	printf("%d\n", max);
	for(i = 0; i < bin; i++) {
		nstars = freq2[i] * nmaxstars / max;
		printf("%d\t|\t", freq2[i]);
		for(j = 0; j < nstars; j++)
			printf("* ");
		printf("\n");
	}
	free(freq1);
	free(freq2);
}
