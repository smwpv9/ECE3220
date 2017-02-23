#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    char* fileName = (char*)malloc(20*sizeof(char));
    printf("Specify file name you would like to print to: \n");
    scanf("%19s", fileName);
 

    FILE* file1 = fopen(fileName, "a+");
 
    char c;
    while ((c=getchar()) != EOF)
    {
        fprintf(file1, &c);
    }
 
    fclose(file1);
 
    printf("CTRL+d is a correct ending");
 
    return 0;
}