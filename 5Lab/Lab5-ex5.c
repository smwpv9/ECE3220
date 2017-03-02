#include<stdio.h>
#include<malloc.h>
void main()
{
	/*Honestly did know what the first program was even going for.
	I solved it by have two different variables but one could've
	malloced, freed, then malloced again then free to not have a mem leak.*/
    char a[] = "hey\0\0\0";
    char b[] = "hello\0";   
    printf("%s",b);
}