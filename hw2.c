#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "lex.yy.c"
#define MAX_SIZE 2048

	
extern int yylex();


char readTokens(){
	
	char* buf = malloc(5);
	int x;
    yyinput();
	return buf[0];
	
	
	
}

int main(){
	
	
	printf("%c -- %d\n",readTokens(),yyin);
	printf("%c -- %d\n",readTokens(),yyin);
	printf("%c -- %d\n",readTokens(),yyin);
	printf("%c -- %d\n",readTokens(),yyin);
	printf("%c -- %d\n",readTokens(),yyin);
	printf("%c -- %d\n",readTokens(),yyin);
	printf("%c -- %d\n",readTokens(),yyin);
	
	return 0;
}




