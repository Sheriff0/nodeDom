#include <stdio.h>
#include <string.h>
char tag[10];
extern char * strIncludes(char s[], char t[]);

extern char * formatAttr(char s[], char t[], _Bool notLine);

extern char * strHasWords(char s[], char t[]);
extern char * getStartOfLine(char s[], int lineNo);

extern _Bool startsWith(char s[], char t[]);

extern int concat(char s[], char *strings[], int len);

extern char * clearExcessSpaces(char s[], char t[], _Bool notLine);

void *getElement(char e[], _Bool tagType,char s[]){
char *openTag[] = {"<", e};
int len = 2;
	
	concat(s, openTag, len);
}

/**char * getElementOfMatched(char *matched){

}**/

void getHTMLattribute(char attr[],char v[], char s[]){
char *class[] = {attr," = \"", v, "\""};
concat(s, class, 4);
}


char * querySelector(char document[], char query[]){
int line;
char expansion[20],trimmedDocLine[1000], *sol, *match = NULL;
		if(startsWith(query, "#")){
	 getHTMLattribute("id",(query+1),expansion);
	 	}else if(startsWith(query, ".")){
	
	  getHTMLattribute("class",(query+1),expansion);
		}else{
	  getElement(query,0,expansion);
		}
	 
      

	 for(line = 1;(sol = getStartOfLine(document, line), *sol) != '\0'; line++){
		clearExcessSpaces(sol, trimmedDocLine, 0);


		if((match = strHasWords(trimmedDocLine, expansion)) != NULL){
		  break;
		}else{
		  continue;
		}

	 }
	
	return (match = strIncludes(document,match), match);
}
/*
char ** querySelectorAll(char document[], char query[]){

}*/

int main(int argc, char **argv){
int i, c;
static char s[5000],fs[5000] ,t[10], *p;
FILE *html = fopen(argv[1], "r");
 for(i = 0;(c = fgetc(html)) != EOF;i++){
	s[i] = c;
 }
 s[i] = '\0';
 formatAttr(s,fs,1);
scanf("%s", t);
printf("%s\n",querySelector(fs, t));
}
