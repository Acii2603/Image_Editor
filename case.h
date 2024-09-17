#pragma once
#pragma pack(1)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load.h"
#include "save.h"
#include "exitfile.h"
#include "select.h"
#include "crop.h"
#include "apply.h"
#include "histogram.h"

// command parser
void cp(img_t *img, char s[100])
{
	/*here we put the command read in main in the type of
	operation, by the first word. afterwards we verify if the
	parameters of the command respect the format */
	char del[] = " \n";
	char *cmd= strtok(s, del);
	if(strcmp(cmd, "LOAD") == 0) {
		char *args = strtok(NULL, del);
		if(!args){
			printf("Invalid command\n");
			return;
		}
		
		if(strtok(NULL, del) != NULL) {
			printf("Invalid command\n");
			return;
		}
		loadfile(img, args);
		return;
	}
	if(strcmp(cmd, "SELECT") == 0) {
		char *args = strtok(NULL, del);
		selectcorners(img, args);
		return ;
	}
	if(strcmp(cmd, "HISTOGRAM") == 0) {
		char *args = strtok(NULL, "\n"), x[3], y[3] = "a", tmp[100];
		if(!img->mat_i && !img->mat_c) {
			printf("No image loaded\n");
			return;
		}
		if(!args) {
			printf("Invalid command\n");
			return;
		}
		strcpy(tmp, args);
		strcpy(x, strtok(tmp, del));
		if(digit(x) == 0) {
			printf("Invalid command\n");
			return;
		}
		strcpy(tmp, args);
		strtok(tmp, del);
		if (strtok(NULL, "\n")) {
			strtok(args, del);
			strcpy(y, strtok(NULL, "\n"));
			if(digit(y) == 0 ) {
				printf("Invalid command\n");
				return;
			}
		}
		if(y[0] == 'a' ) {
			printf("Invalid command\n");
			return;
		}

		if(strtok(NULL, del) != NULL) {
			printf("Invalid command\n");
			return;
		}

		histogram(img, x, y);
		return;
	}

	// if(strcmp(s, "EQUALIZE") == 0)
	//     return 5;
	if(strcmp(s, "ROTATE") == 0) {
		char *args = strtok(NULL, del);
		if(args[0] == '-') {
			args[0] = args[1];
			args[1] = args[2];
			args[2] = args[3];
		}
		if(number(args) % 90 != 0) {
			printf("Unsupported rotation angle\n");
			return;
		}
		if(strtok(NULL, del) != NULL) {
			printf("Invalid command\n");
			return;
		}
		if(!img->mat_i && !img->mat_c) {
			printf("No image loaded\n");
			return;
		}
		if (img->x1 != img->x2 || img->y1 != img->y2) {
			printf("The selection must be square\n");
			return;
		}
		printf("Rotated %s", args);
	}

	if(strcmp(cmd, "CROP") == 0) {
		crop(img);
		return;
	}
	if(strcmp(cmd, "APPLY") == 0) {
		char *args = strtok(NULL, del);
		if(!img->mat_c && !img->mat_i) {
		printf("No image loaded\n");
		return;
	}
		if(!args){
			printf("Invalid command\n");
			return;
		}
		if(strtok(NULL, del) != NULL) {
			printf("Invalid command\n");
			return;
		}
		apply(img, args);
		return;
	}
	if(strcmp(cmd, "SAVE") == 0) {
		char *args = strtok(NULL, "\n"), filetype[6], filename[100], tmp[100], tmp2[100];
		if(!args) {
			printf("Invalid command\n");
			return;
		}
		strcpy(tmp, args);
		strcpy(filename, strtok(tmp, del));
		strcpy(tmp, args);
		strtok(tmp, del);
		if (strtok(NULL, "\n")) {
			strtok(args, del);
			strcpy(tmp2, strtok(NULL, "\n"));
			if(strcmp(tmp2, "ascii") == 0)
				strcpy(filetype, "ascii");
			else {
				printf("Invalid command\n");
				return;
			}
		} else {
			filetype[0] = 'b';
		}
		savefile(img, filename, filetype);
		return;
	}
	if(strcmp(cmd, "EXIT") == 0) {
		exitfile(img);
		return;
	}
	printf("Invalid command\n");
	return;
}
