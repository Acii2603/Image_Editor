#pragma once

// the struct for color pictures
typedef struct {
	unsigned char R; //red
	unsigned char G; //green
	unsigned char B; //blue
} pixelcol_t;

/* i defined here a struct that
contains informations about the image type
*/
typedef struct img {
	char type[3];
	int height;
	int width;
	int max;
	unsigned char **mat_i;
	pixelcol_t **mat_c;
	int x1, x2, y1, y2;
} img_t;
