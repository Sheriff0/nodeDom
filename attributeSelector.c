/****
-o attributeSelector
getDomString.c
strings.c
#*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
extern _Bool strCompInC(char s[], char c, char t[]);

extern void getHTMLattribute(char attr[],char v[], char s[], _Bool term);

extern char * clearExcessSpaces(char s[], _Bool notLine);

extern char * appendS(char t[], char s[], char y[]);

extern char * prependS(char t[], char s[],char y[]);

char * attributeSelector(char s[], char selector[]){
static char att[20], val[100], c, expansion[100];
int i = 0;
	while((c = selector[i]) != '|' && c != '~' && c != '=' && c != '^' && c != '\0'){
	i++;
	}
	if(c == '='){
	 getWordBeyond(selector+i, '=',val);
	 getWordBeyond(selector,'[',att);
	 getHTMLattribute(att, val, expansion,1);
	}else if(c == '|'){
	getWordBeyond(selector+i,'=',val);
	appendC(val, '-');
	getWordBeyond(selector, '[',att);
	getHTMLattribute(att,val,expansion,0);
	}else if(c == '^'){
	getWordBeyond(selector+i,'=',val);
	getWordBeyond(selector, '[',att);
	getHTMLattribute(att,val,expansion,0);
	}
	return expansion;
}

int main(int argc, char *argv[]){
int c, i;
char str[1000];
	/*
	for(i = 0;(c = getchar()) != EOF;i++){
	 str[i] = c;
	}
	str[i] = '\0';*/
printf("%s\n", spaceSepValComp(str,argv[1]));
}
