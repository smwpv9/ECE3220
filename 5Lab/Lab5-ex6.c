#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	char *ch;
	ch= (char*)malloc(sizeof(char)*2);//needed to not dereference. and cast the malloc.
	ch[1]='3';
	ch[2]='a';
	while (ch[1] > '0') 
	{
		printf("Character: %c and %c\n", ch[1], ch[2]);
		ch[1]--;
	}
	printf(" main:%p\n ch:%p\n ch+1:%p\n ch+2:%p\n ",&main,ch,ch+1,ch+2);
	free( ch );//NO memory leaks
	return 0;//proper return statement.
}