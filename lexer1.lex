%{
/* Declarations section */
#include <stdio.h>
#define MAX_LEN 2048
void showToken(char *,char *);
void showToken2(char *,char *);
void showToken3(char *);
void showToken4(char *);
void showToken5(char *);
void streamE();
void stringE();
void stringE1();
void stringE2(char a);
void stringE3();
void error();
void error2();
void hex2ascii();
%}
%option yylineno
%option noyywrap
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n\r ])
%x ENDSTREAM STRING STRING2
%%
obj showToken("obj","OBJ");
endobj showToken("endobj","ENDOBJ");
\[ showToken("[","LBRACE");
\] showToken("]","RBRACE");
\<\< showToken("<<","LDICT");
\>\> showToken(">>","RDICT");
(\%)(.)*([\n\r]|[\r][\n]) showToken2(yytext,"COMMENT");
true showToken("true","TRUE");
false showToken("false","FALSE");
((\+|\-)?){digit}+ showToken(yytext,"INTEGER");
((\+|\-)?)((({digit}*)(\.)({digit}+))|(({digit}+)(\.))) showToken(yytext,"REAL");
\/({letter}|{digit})({letter}|{digit})* showToken(yytext,"NAME");
(stream[\r][\n])|(stream[\n\r]) BEGIN(ENDSTREAM);
<ENDSTREAM>((.)|{whitespace}) streamE();
<ENDSTREAM>'(0)' printf("");
<ENDSTREAM>([\r][\n]endstream)|([\n\r]endstream) {showToken5("STREAM");BEGIN(INITIAL);}
<ENDSTREAM><<EOF>> {printf("Error unclosed stream\n");exit(0);}
\< BEGIN(STRING2);
<STRING2>({digit}|[A-Fa-f]){whitespace}*({digit}|[A-Fa-f]) hex2ascii();
<STRING2>{whitespace}+ {printf("");}
<STRING2>({digit}|[A-Fa-f]) {printf("Error incomplete byte\n");exit(0);}
<STRING2>\> {showToken4("STRING");BEGIN(INITIAL);}
<STRING2><<EOF>> {printf("Error unclosed string\n");exit(0);}
<STRING2>[^A-Fa-f0-9] {error(); exit(0);}
\( BEGIN(STRING);
<STRING>\\[0-2][0-7][0-7] stringE3();
<STRING>\\\) stringE1();
<STRING>\\\( stringE1();
<STRING>\\\\ stringE1();
<STRING>(\\n) stringE2('\n');
<STRING>(\\b) stringE2('\b');
<STRING>(\\r) stringE2('\r');
<STRING>(\\t) stringE2('\t');
<STRING>(\\f) stringE2('\f');
<STRING>\( error();
<STRING>([\n\r]|[\r][\n]) {printf("Error \r\n"); exit(0);}
<STRING>\\{whitespace}+ stringE();
<STRING>\\. {error2(); exit(0);}
<STRING>\) {showToken4("STRING");BEGIN(INITIAL);}
<STRING><<EOF>> {printf("Error unclosed string\n");exit(0);}
<STRING>((.)|{whitespace}) streamE();
null showToken("null","NULL");
{whitespace}+ printf("");
<<EOF>> {showToken(yytext,"EOF");exit(0);}
. error();
%%
int i=0;

char tmp[MAX_LEN];
void streamE(){
tmp[i++]=*yytext;
tmp[i]='\0';
}
void stringE(){
tmp[i]='\0';
}
void stringE1(){
tmp[i++]=*(yytext+1);
tmp[i]='\0';
}
void stringE2(char a){
tmp[i++]=a;
tmp[i]='\0';
}
void stringE3(){
int num1=(*(yytext+1))-'0',num2=(*(yytext+2))-'0',num3=(*(yytext+3))-'0';
tmp[i++]=(num1*64)+(num2*8)+(num3);
tmp[i]='\0';
}
void showToken(char * name,char * type)
{
 printf("%d %s %s\n",yylineno,type, name);
}
void showToken2(char * name,char * type)
{
if(name[yyleng-1]=='\n' && name[yyleng-2]=='\r')
name[yyleng-2]='\0';
else{
name[yyleng-1]='\0';
}

 printf("%d %s %s\n",yylineno-1,type, name);
} 
void showToken3(char * type)
{
 printf("%d %s %s",yylineno,type, tmp);
 i=0;
 tmp[i]='\0';
} 
void showToken5(char * type)
{
 printf("%d %s %s\n",yylineno,type, tmp);
 i=0;
 tmp[i]='\0';
} 
void showToken4(char * type)
{
 printf("%d %s %s\n",yylineno,type, tmp);
 i=0;
 tmp[i]='\0';
} 
void error(){
 printf("Error %s\n",yytext);
 exit(0);
}
void error2(){
printf("Error undefined escape sequence %c\n",*(yytext+1));
exit(0);
}
void hex2ascii(){
int tmp2,tmp1;
char first,second;
int flag=0;
int j=0;
for( j=0;j<yyleng;j++){
if((*(yytext+j))!='\t' && (*(yytext+j)) != '\n' && (*(yytext+j))!= '\r' && (*(yytext+j))!= ' '){
if(flag==0){
first=(*(yytext+j));
flag=1;
}
else{
second=(*(yytext+j));
}
}
}
if(first<='9' && first>='0'){
tmp2=(first)-'0';
}
if(second<='9' && second>='0'){
tmp1=(second)-'0';
}
if(first=='a'| first=='A'){
tmp2=10;
}
if(first=='b' | first=='B'){
tmp2=11;
}
if(first=='c'| first=='C'){
tmp2=12;
}
if(first=='d'| first=='D'){
tmp2=13;
}
if(first=='e'| first=='E'){
tmp2=14;
}
if(first=='f'| first=='F'){
tmp2=15;
}
if(second=='a'| second=='A'){
tmp1=10;
}
if(second=='b' | second=='B'){
tmp1=11;
}
if(second=='c'| second=='C'){
tmp1=12;
}
if(second=='d'| second=='D'){
tmp1=13;
}
if(second=='e'| second=='E'){
tmp1=14;
}
if(second=='f'| second=='F'){
tmp1=15;
}

tmp[i++]=(tmp2*16)+tmp1;
tmp[i]='\0';
}
