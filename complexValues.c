extern char * appendS(char t[], char s[],char y[]);

extern char * prependS(char t[], char s[], char y[]);

createComplexValue(){

}

_Bool spaceSepValComp(char s[], char v[]){
char *vals[3], temp[2000];
vals[0] = prependS(v,"\"",temp);
vals[1] = appendS(prependS(v," ", temp)," ",temp);
vals[2] = appendS(v,"\"",temp);
}
