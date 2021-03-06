#include <stdio.h>
#include <string.h>
#define NEWline '\n'
int newLineC(char *str)
{
 int newLines = 0;
while(*str != '\0'){
if(*str == NEWline){
newLines++;
}
str++;
}
return newLines;
}

_Bool str_includes(char s[], char t[]){
int i, i2 = 0;
char *c;
  for(i = 0;*(c = s+i) != '\0'; i++){
	for(i2 = 0;t[i2] != '\0' && *(c+i2) == *(t+i2);i2++){
	;
	}
	if(t[i2] == '\0'){
	return (_Bool) 1;
	}
  }
  return (_Bool) 0;
}

char ** stringify(char t[], char at){
#define MAX 100
int i = 0, i1 = 0;
char c, *offs[MAX];
offs[i1++] = t;
	while((c = t[i]) != '\0'){
	if(c == at){
	t[i] = '\0';
	offs[i1] = t+i+1;
	i1++;
	   }
	i++;
	}
	return offs;
}


#define LIC leastIndexCheckable
int mda_includes(char *mda[], char t[],int len, int LIC){/*mULTI-dIMENTIONAL aRRAY*/
	--len;
	while(len >= LIC){
	if(str_includes(mda[len], t)){
	return  len;	
		}
		len--;
	}
	
	return -2;
}

int main(int argc, char **argv){
	if(argc > 1){
	FILE *fp = fopen(argv[argc-1], "r");
	int c, i, lines;
char str[1000], st[50];
	
	if(fp != NULL){
	for(i = 0;(c = fgetc(fp)) != EOF;i++){
	 str[i] = c;
	}
	str[i] = '\0';
	lines = newLineC(str);
	if(mda_includes(argv, "o", argc-1, 1) >= 0 || argc == 2/*the output option*/){	
	fprintf(stdout,"%s", str);
	}

	if(mda_includes(argv, "i", argc-1, 1) >= 0/*get input option*/){
	scanf("%s", st);
		if((i = strlen(st)) >= 1 && (c = mda_includes(stringify(str, '\n'), st, lines, 0)) >= 0){
	fprintf(stdout, "%i\n", c);
		}else if(i < 1){
	fprintf(stderr, "\033[0;31mYour input should be at least 1 character\n");	
		}else{
	fprintf(stderr, "\033[0;31mThe string %s does not exist\n", st);	
		}
	}
	
	

	fclose(fp);
	}else{
	fprintf(stderr, "There was a problem opening file %s\n", argv[argc-1]);
	}

	}else{
	fprintf(stderr, "Please enter a file to open\n(Hint : display file.txt)\n");
	}
	return 0;
}
