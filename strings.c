#include <stdio.h>
#include <ctype.h>
#include <string.h>
char *strCopyUptoC(char s[], char c, char t[]){
int i = 0;
	while(s[i] != c && s[i] != '\0'){
	  *(t+i) = s[i];
	  i++;
	}

	if(s[i] == c){
	   *(t+(i++)) = c;
	   *(t+i) = '\0';
	   return t;
	}else{
	   return NULL;
	}
}

_Bool strCompInC(char s, char c){
extern char * strCopyUptoC(char s[], char c, char t[]);
	
}

char * formatAttr(char s[], char t[], _Bool notLine){
int i,i1;
char c, c1;
 c1 = (!notLine)? '\n' : '\0';
	for(i1 = i = 0;(c = *(s+i)) != c1;i++){
	     if(!isspace(c) && *(s+i+1) == '='){
		*(t+(i1++)) = c;	
		*(t+(i1++)) = ' ';
	     }else if(!isspace(c) && *(s+i-1) == '='){
		*(t+(i1++)) = ' ';
		*(t+(i1++)) = c;
	     }else{
	        *(t+(i1++)) = c;
	     }
	}
	  *(t+i1) = '\0';
	  return t;
}

char * strHasWords(char s[], char t[]){
int i, i2 = 0;
char *c;
  for(i = 0;*(c = s+i) != '\0'; i++){
	for(i2 = 0;t[i2] != '\0' && *(c+i2) == *(t+i2);i2++){
	;
	}
	if(t[i2] == '\0' && !isalnum(*(c+i2))){
	return (c);
	}
  }
  return NULL;
}

char * clearExcessSpaces(char s[],_Bool notLine){
int i,i1;
char c, c1,t[2000];
 c1 = (!notLine)? '\n' : '\0';
	for(i1 = i = 0;(c = *(s+i)) != c1;i++){
	     if(isspace(c) && isspace(*(s+i+1))){
		continue;
	     }else{
		*(t+(i1++)) = c;
	     }
	}
	  *(t+i1) = '\0';
	  strcpy(s,t);
	  return s;
}

int strCopy(char s[], char t[], int cont){
int i = 0, i1;
if(cont > 0){
i = cont;
}
  for(i1 = 0; t[i1] != '\0'; i1++){
	*(s+(i++)) = t[i1];
 	 }

  return  i;
}

int strCat(char s[], char t[], int cont){
int i = 0, i1;
if(cont == 0){
  for(; s[i] != '\0'; i++){
    ;
 	 }
}
   i += cont;

  for(i1 = 0; t[i1] != '\0'; i1++){
	s[i++] = t[i1];
 	 }

  return  i;
}

_Bool startsWith(char s[], char t[]){
int i;
  for(i = 0;s[i] == t[i] && t[i] != '\0';i++){
	;
  }
  return (t[i] == '\0' && s[i-1] == t[i-1])? 1 : 0;
}

char * trim(char s[], _Bool notLine){
char c, c1,t[2000];
int i, i1;
c1 = (!notLine)? '\n' : '\0';
    for(i = i1 = 0;(c = s[i]) != c1;i++){
	  if(isspace(c)){
		continue;
	  }else{
	    *(t+(i1++)) = c;
	  }
    }
    *(t+i1) = '\0';
    strcpy(s,t);
    return s;
}

char * getStartOfLine(char s[], int lineNo){
int i, linesPassed;
char c, *startOfLine;
    for(startOfLine = s,linesPassed = 1, i = 0;(c = s[i]) != '\0' && linesPassed != lineNo; i++){
	if(c == '\n'){
	  startOfLine = (s+i+1);
	  linesPassed++;
	}else{
	   continue;
	}
    }
    return (linesPassed == lineNo)? startOfLine : NULL;
}

char * strIncludes(char s[], char t[]){
int i, i2 = 0;
char *c;
   if(*t != '\0'){
  for(i = 0;*(c = s+i) != '\0'; i++){
	for(i2 = 0;*(t+i2) != '\0' && *(c+i2) == *(t+i2);i2++){
	;
		}
	if(*(t+i2) == '\0'){
	return c;
	}
  }
}
  return NULL;
}

/*
int main(int argc,char **argv){
char s[2000], t[2000], *l;
int c, i;
      for(i = 0;(c = getchar()) != EOF;i++){
	      s[i] = c;
      }
      s[i] = '\0';
      
      
printf("%s\n", clearExcessSpaces(s,t));
}*/
