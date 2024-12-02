#include <stdio.h>
#include "cat.h"

void execute_cat(const char *file) {
    if (file == NULL) {
        printf("Usage: cat [filename]\n");
        return;
    }

    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
}
