 
#include<stdio.h>
#include<string.h>
int main()
{
    int i=0;
    char arr1[ 15 ] = "Trumantiger";
    char arr2[ 20 ];
    while(i<20){
        arr2[ i ] = 'a';
	++i;
    }
	arr2[ 0 ] = 'b';
    strcpy( arr1 , arr2 );
	arr1[ 14 ] = '\0';
    printf("%s",arr1);
	return 0;
}