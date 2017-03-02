 
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
    strcpy( arr1 , arr2 ); // My system doesn't notice that this is writing into space it shouldn't
	arr1[ 14 ] = '\0';//strcpy doesn't copy the null terminator over.
    printf("%s",arr1);
	return 0;
}