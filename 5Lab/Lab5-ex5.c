#include<stdio.h>
#include<malloc.h>
void main()
{
    char a[] = "hey\0\0\0";
    char b[] = "hello\0";   
    printf("%s",b);
}