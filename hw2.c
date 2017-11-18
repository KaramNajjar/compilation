#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "lex.yy.c"
#include "AST.h"
#define MAX_SIZE 2048

	
extern int yylex();
tokens current = (tokens)yylex();

char readTokens(){
	
    int t = yylex();
	printf("%d\n",t);
}

void error(){
	printf("Syntax error\n");
	exit(0);
}
ObjNode* Obj(){
	
	printf("Producing Obj\n");
	ObjNode* root ;
	
	if(current == INTEGER){
		
		match(INTEGER);
		match(INTEGER);
		match(OBJ);
		root = new ObjNode(Body());
		match(ENDOBJ);
		
		
	}else{
		error();
	}
	
	printf("Finished producing Obj\n");
	return root;
	
}
BodyNode* Body(){
	
	printf("Producing Body\n");
	BodyNode* node;
	
	node = new BodyNode(Dict());
	
	printf("Finished producing Body\n");
	return node;
	
}
DictNode* Dict(){
	
	printf("Producing Dict\n");
	DictNode* node;
	
	if(current == LDICT){
		
		match(LDICT);
		if(current == RDICT){
			match(RDICT);
			printf("Producing KVList\n");
			node = new DictNode(new KVListNode());
			printf("Finished producing KVList\n");

		}
		else{
			node = new DictNode(KVList());
			match(RDICT);
		}	
		
	}else{
		error();
	}
	
	printf("Finished producing Dict\n");
	return node;
	
}
KVListNode* KVList(){
	
	printf("Producing KVList\n");
	KVListNode* node;
	
	if(current == NAME)
		node = new KVListNode(KV(),KVList());

	
	printf("Finished producing KVList\n");
	return node;
	
}

KVNode* KV(){
	
	printf("Producing KV\n");
	if(current == NAME){
		
		match(NAME);
		node = new KVNode(Exp());
	}else{
		error();
	}
	printf("Finished producing KV\n");
	return node;
	
}

ExpNode* Exp(){
	
	printf("Producing Exp\n");
	
	switch(current){
		
		case INTEGER: match(INTEGER); break;
		case REAL: match(REAL); break;
		case STRING: match(STRING); break;
		case TRUE: match(TRUE); break;
		case FALSE: match(FALSE); break;
		case NUL: match(NUL); break;
		default : error(); break;
	}
	
	
	printf("Finished producing Exp\n");
	return new ExpNode();
}
void match(tokens t){
	
	if(current == t){
		current = (tokens)yylex();
	}else{
		error();
	}
}

int main(){
	
	ObjNode* root = obj();
	root->prettyPrint();
	delete root;

	
	return 0;
}




