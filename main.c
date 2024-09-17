// Copyright Alexandru-Andrei Ionita 312CAa 2022-2023
#include <stdio.h>
#include "case.h"

int main(){
    char s[100];
    img_t img;
    img.mat_c = NULL;
    img.mat_i = NULL;
    while(1) {
        fgets(s, 100, stdin);
        cp(&img, s);
    }
}
