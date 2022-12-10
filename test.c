#include <stdio.h>
#include <stdlib.h>
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
typedef unsigned char data;
typedef unsigned short address;

typedef struct {
    int x;
    int y;
} check;

void offsetChecker(check *base, size_t offset){
    int *adr;
    // adr = (int*)((char*)base + offset);
    printf("%lu\n", offset);
}
int main(){
    check *newPtr = (check *)malloc(sizeof(check));
    newPtr->x = 10;
    newPtr->y = 20;
    offsetChecker(newPtr, OFFSETOF(check, y));
    return 0;
}
