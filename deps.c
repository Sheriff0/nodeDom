/****
-o deps.out
deps.c	
strings.c


concat.c
#***/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int appendS(char t[], char s[]){
extern int appendC(char s[], char c);
char c;
int i = 0;

	while(s[i+1] != '\0'){
	 c = *(s+(i));
	 appendC(t,c);
	 i++;
	}
	
	return appendC(t,s[i]);
}

int appendC(char s[], char c){
char temp[20000], c1;
int i;
	for(i = 0;(c1 = s[i]) != '\0';i++){
	 *(temp+i) = c1;
	}
	*(temp+(i++)) = c;
	*(temp+i) = '\0';
	strcpy(s,temp);
	return i;

}

char * prependC(char s[], char c){
char temp[20000], c1;
int i;
*temp = c;
	for(i = 1;(c1 = s[i-1]) != '\0';i++){
	 *(temp+i) = c1;
	}
	*(temp+i) = '\0';
	strcpy(s,temp);
	return s;
}

char * prependS(char t[], char s[]){
extern char * prependC(char s[], char c);
int i = strlen(s);
char c;
i--;
	while((s+i) >= s){
	 c = *(s+i);
	 prependC(t,c);
	 i--;
	}
	return t;
}

char * appendDep(FILE *fp, char deped[],char *files[], int len){
#define IN 1
#define OUT 0
int c, i, stars, nl, slash, i1,c1, state = OUT;
stars = nl = slash = 0;
i1 = 1;
	for(i = 0;(c = fgetc(fp)) != EOF;i++){
		if(c == '*'){
		  stars++;
		}else if(c == '/'){
		  slash++;
		}

		if(stars == 4 && slash == 1){
		 state = IN;
		}

	if((c1 = fgetc(fp)) == '#' && state == IN){
		*(deped+(i++)) = c;
		*(deped+i) = '\0';
		while(i1 < len){
		i = appendS(deped,files[i1]);	
		*(deped+(i++)) = '\n';
		*(deped+i) = '\0';
		 i1++;	
		}

		  state = OUT;
		  i--;
		}else{
		 *(deped+i) = c;
		}
	ungetc(c1, fp);
	}
	*(deped+i) = '\0';
	return deped;
}

char * makeDeps(FILE *fp, char deped[], char *files[],int len){
int i,c;
char filename[100];
strcpy(filename,files[len]);
c = strlen(filename);
filename[c-2] = '\0';
	for(i = 0;(c = fgetc(fp)) != EOF;i++){
	 *(deped+i) = c;
	}
	*(deped+i) = '\0';
	prependS(deped,"\n#/\n");
	len--;
	  while(len > 0){
		prependS(deped, files[len]);
		prependS(deped, "\n");
		len--;
	  }
	  prependS(deped, filename);
	  prependS(deped, "/****\n");
	  return deped;
}

char * readDep(FILE *openedFile, char deps[]){
extern char * fetchDeps(FILE *fp, char deps[]);
int stars = 0, slash = 0, nl = 0;
int c;
   while((c = fgetc(openedFile)) != EOF && (stars != 4 || slash != 1) && nl == 0){
	if(c == '*'){
	stars++;
	}else if(c == '/'){
	 slash++;
	}else if(c == '\n'){
	 nl++;
	}
   }
   if(c == EOF || nl > 0){
	return NULL;
   }else{
	fetchDeps(openedFile, deps);
	return deps;
   }
}

char * fetchDeps(FILE *fp, char deps[]){
int i, c, c1;
	for(i = 0;(c1 = fgetc(fp)) != EOF && c1 != '#' && c != '*';){
	       if(isspace((c = fgetc(fp))) && isspace(c1)){
		   ungetc(c, fp);
		   continue;
	       }else{
		   deps[i++] = (isspace(c1))? ' ' : c1;
		   ungetc(c, fp);
	       }
	}
	deps[i] = '\0';
	return deps;

}

int main(int argc, char **argv){
FILE *fp = fopen(argv[argc-1], "r");
char s[4000];
    makeDeps(fp, s,argv,argc-1);
    fclose(fp);
    fprintf(stdout,"%s\n",s);
}
