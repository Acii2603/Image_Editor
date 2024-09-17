#pragma once
#pragma pack(1)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

//we have a function to verify if our string is a number
int digit(char *s)
{
	char cpy[100];
	int i = 0;
	strcpy(cpy, s);
	cpy[strlen(cpy)] = '\n';
	while(cpy[i] != '\n') {
		if(cpy[i] < '0' || cpy[i] > '9') {
			return 0;
		}
		i++;
	}
	return 1;
}

//here we make the string into a number
int num(char s[100])
{
	char cpy[100];
	int rez = 0;
	int i = 0;
	strcpy(cpy, s);
	cpy[strlen(cpy)] = '\n';
	while(cpy[i] != '\n') {
		if(cpy[i] >= '0' || cpy[i] <= '9') {
			rez = rez * 10 + (cpy[i] - '0');
		}
		i++;
	}
	return rez;
}


//here we have both select and select all, depending on the first word/number after SELECT
void selectcorners(img_t *img, char s[100])
{
	char del[] = " \n";
	int v[4], ok = 0;
	if(!s) {
		printf("Invalid set of coordinates\n");
		return;
	}
	//if we have ALL we reset the positions
	if(strcmp(s, "ALL") == 0) {
		if (!img->mat_c && !img->mat_i) {
			printf("No image loaded\n");
			return ;
		}
		img->x1 = 0;
		img->y1 = 0;
		img->x2 = img->width;
		img->y2 = img->height;
		printf("Selected ALL\n");
		return;
	} 
	//otherwise, we verify if our numbers are positive
	if(s[0] == '-') {
		printf("Invalid set of coordinates\n");
		return;
	}
	//if we have a number we verify the others
	if(digit(s) == 1) {
		if (!img->mat_c && !img->mat_i) {
			printf("No image loaded\n");
			return;
		}
		//here we verify that all the following set of values that they are positive integers
		while(s != NULL && ok <4) {
			if(s[0] == '-') {
				printf("Invalid set of coordinates\n");
				return;
			}
			if(digit(s) == 0) {
				printf("Invalid set of coordinates\n");
				return;
			}
			v[ok] = num(s);
			s = strtok(NULL, del);
			ok++;
		}
		if(ok < 4 || s) {
			printf("Invalid set of coordinates\n");
			return;
		}
		//we swtich the values if they are in the wrong order
		if(v[0] > v[2]) {
			v[0] = v[0] + v[2];
			v[2] = v[0] - v[2];
			v[0] = v[0] - v[2];
		}
		if(v[1] > v[3]) {
			v[1] = v[1] + v[3];
			v[3] = v[1] - v[3];
			v[1] = v[1] - v[3];
		}
		if(v[0] < 0 || v[1] < 0 || v[2] > img->width || v[3] > img->height) {
			printf("Invalid set of coordinates\n");
			return;
		}
		if(v[0] == v[1] && v[1] == v[2] && v[2] == v[3]) {
			printf("Invalid set of coordinates\n");
			return;
		}
		img->x1 = v[0];
		img->y1 = v[1];
		img->x2 = v[2];
		img->y2 = v[3];
		printf("Selected %d %d %d %d\n",v[0], v[1], v[2], v[3]);
	}
}
