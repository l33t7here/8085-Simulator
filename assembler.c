#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char *trim(char *value){
    while (*value == ' ')
    {
        value++;
    }
    return value;
}

void testGetFile() {
    // open file
    FILE *fp = fopen("demo.asm", "r");
    size_t len = 255;
    // need malloc memory for line, if not, segmentation fault error will occurred.
    char *line = malloc(sizeof(char) * len);
    // check if file exist (and you can open it) or not
    if (fp == NULL) {
        printf("can open file input1.txt!");
        return;
    }
    while(fgets(line, len, fp) != NULL) {
        printf("%s", line);
    }
    free(line);
}

int main(){
    // testGetFile();
    char *check = strpbrk("Hello, I am here", ",");
    // printf("%s\t",  trim(check));
    trim(check+1);
    return 0;
}

