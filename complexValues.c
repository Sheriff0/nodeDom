#include <stdio.h>
/****
-g
-o complexValues
strings.c
#*/


extern _Bool strCompInC(char s[], char c, char t[]);

extern char * appendS(char t[], char s[],char y[]);

extern char * prependS(char t[], char s[], char y[]);

createComplexValue(){

}

_Bool spaceSepValComp(char s[], char v[]){
char temp[2000];
   if(strCompInC(s,'"',prependS(v,"\"",temp))){
	return 1;
   }else if(strCompInC(s,'"',appendS(prependS(v," ", temp)," ",temp))){
	return 1;
   }else if(strCompInC(s,'"',appendS(v,"\"",temp))){
	return 1;
   }else{
	return 0;
   }


}

int main(int argc, char **argv){
int i, c;
char s[100];
	for(i = 0;(c = getchar()) != EOF;i++){
	  s[i] = c;
	}
	s[i] = '\0';
printf("%i\n",spaceSepValComp(s, argv[1]));
}
