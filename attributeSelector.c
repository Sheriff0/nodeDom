#include <stdio.h>
#include <ctype.h>
#include <string.h>
extern _Bool spaceSepValComp(char s[], char v[]);

extern void getHTMLattribute(char attr[],char v[], char s[], _Bool term);

extern char * clearExcessSpaces(char s[], _Bool notLine);

char * appendS(char t[], char s[], char y[]){
extern char * appendC(char s[], char c);
char c;
int i = 0;
   strcpy(y,t);

	while(s[i] != '\0'){
	 c = *(s+i);
	 appendC(y,c);
	 i++;
	}
	return y;
}

char * appendC(char s[], char c){
char temp[2000], c1;
int i;
	for(i = 0;(c1 = s[i]) != '\0';i++){
	 *(temp+i) = c1;
	}
	*(temp+(i++)) = c;
	*(temp+i) = '\0';
	strcpy(s,temp);
	return s;

}

char * prependC(char s[], char c){
char temp[2000], c1;
int i;
*temp = c;
	for(i = 1;(c1 = s[i-1]) != '\0';i++){
	 *(temp+i) = c1;
	}
	*(temp+i) = '\0';
	strcpy(s,temp);
	return s;
}

char * prependS(char t[], char s[],char y[]){
extern char * prependC(char s[], char c);
int i = strlen(s);
char c;
i--;
  strcpy(y,t);
	while((s+i) >= s){
	 c = *(s+i);
	 prependC(y,c);
	 i--;
	}
	return y;
}

char * getWordBeyond(char s[], char c, char word[]){
int i = 0;
extern char * getWord(char s[], char word[]);
    while(s[i] != c){
     i++;
    }
    i++;
    while(!(isalnum(s[i]))){
	i++;
    }
return getWord(s+i, word);

}

char * getWord(char s[], char word[]){
int i = 0;
    do{
	*(word+i) = s[i];
	i++;
    }while(*(s+i) != '"' && *(s+i) != '\'' && *(s+i) != ']' && *(s+i) != '\0' && s[i] != '=' && s[i] != '^');
    return (*(word+i) = '\0', word);
}

char * attributeSelector(/*char doc[],*/ char selector[]){
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
