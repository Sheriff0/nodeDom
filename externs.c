#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define LIC leastIndexCheckable

/**********Utils*************/
int stringify(char t[], char at, char *mda[]){

int i = 0, i1 = 0;
char c;
*(mda+(i1++)) = t;
	while((c = t[i]) != '\0'){
	if(c == at){
	t[i] = '\0';
	*(mda+i1) = t+i+1;
	i1++;
	   }
	i++;
	}
	return (i1-1);
}

_Bool startsWith(char s[], char t[]){
int i;
  for(i = 0;s[i] == t[i] && t[i] != '\0';i++){
	;
  }
  return (t[i] == '\0' && s[i-1] == t[i-1])? 1 : 0;
}

_Bool sIncludes(char s[], char t[]){
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


int mdaIncludes(char *mda[], char t[],int len, int LIC){/*mULTI-dIMENTIONAL aRRAY*/
extern _Bool sIncludes(char s[], char t[]);
	--len;
	while(len >= LIC){
	if(sIncludes(mda[len], t)){
	return  len;	
		}
		len--;
	}
	
	return -2;
}

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

/*********** CORES**********/
char * readDepsDeps(FILE *fp, char t[]){
int i = 0, c, stars = 0,slash = 0,c1;
	while(t[i] != '\0'){
	  i++;
	}
	 for(;(c = fgetc(fp)) != EOF && c != '#';){
		
		 if(c == '-' && stars == 4 && slash == 1){
		  while((c1 = fgetc(fp)) != '\n'){
			;
		  }
		
	       }else if(stars == 4 && slash == 1){
		*(t+(i++)) = (isspace(c))? ' ' : c;
	       }

	       if(c == '/'){
		slash++;
	     while((c1 = fgetc(fp)) == '*'){
	       stars++;
	     }
	     	  if(stars != 4){
		stars = 0;
		slash = 0;
	    	   }
	     ungetc(c1,fp);
		}		
	       
	 }
	 *(t+(i)) = '\0';
	 return t;
}


char * appendDeps(FILE *fp, char deped[],char *files[], int len, int LIC){
#define IN 1
#define OUT 0
int c, i, stars, nl, slash, i1,c1, c2,state = OUT;
stars = nl = slash = 0;
i1 = 1;
	for(i = 0;(c = fgetc(fp)) != EOF;i++){
		if(c == '/'){
		  slash++;
		   *(deped+(i++)) = c;
			while((c2 = fgetc(fp)) == '*'){
	       stars++;
	     *(deped+(i++)) = c2;
	     }
	     if(stars != 4){
		stars = 0;
		slash = 0;
	     }
	     c = c2;
		}

		if(stars == 4 && slash == 1){
		 state = IN;
		}

	if((c1 = fgetc(fp)) == '#' && state == IN){
		*(deped+(i++)) = c;
		*(deped+i) = '\0';
		i1 = LIC;
		while(i1 < len){
			if(!startsWith(files[i1], "-")){
		i = appendS(deped,files[i1]);	
		*(deped+(i++)) = '\n';
		*(deped+i) = '\0';
			}
		 i1++;	
		}

		  state = OUT;
		  stars = 0;
		  i--;
		}else{
		 *(deped+i) = c;
		}
	ungetc(c1, fp);
	}
	*(deped+i) = '\0';
	return deped;
}

char * makeDeps(FILE *fp, char deped[], char *files[],int len, int LIC, _Bool dev){
int i,c;
	char filenameD[100] = {'-','g','\n','-', 'o', ' ', '\0'},filename[100] = {'-', 'o', ' ', '\0'};

	if(dev){
	appendS(filenameD,files[len]);
	c = strlen(filenameD);
	filenameD[c-2] = '\0';
	}else{
	appendS(filename,files[len]);
	c = strlen(filename);
	filename[c-2] = '\0';
	}
	for(i = 0;(c = fgetc(fp)) != EOF;i++){
	 *(deped+i) = c;
	}
	*(deped+i) = '\0';
	prependS(deped,"\n#*/\n");
	len--;
	  while(len >= LIC){
		if(!startsWith(files[len], "-")){
		prependS(deped, files[len]);
		prependS(deped, "\n");
		}
		len--;
	  }
	if(dev){ 
	prependS(deped, filenameD);
	}else{
	prependS(deped, filename);
	}
	  prependS(deped, "/****\n");
	  return deped;
}

char * readDeps(FILE *openedFile, char deps[]){
extern char * fetchDeps(FILE *fp, char deps[]);
int stars = 0, slash = 0, c,c1;
   while((c = fgetc(openedFile)) != EOF && (stars != 4 || slash != 1)){
	if(c == '/'){
		slash++;
	     while((c1 = fgetc(openedFile)) == '*'){
	       stars++;
	     }
	     if(stars != 4){
		stars = 0;
		slash = 0;
	     }
	     ungetc(c1,openedFile);
	}
   }
   if(c == EOF){
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

int mdaIncludes(char *mda[], char t[],int len, int LIC);

int main(int argc, char **argv){
char filename[100];
strcpy(filename,argv[argc-1]);
FILE *fp = fopen(filename, "r");
	char s[50000], *deps[100],res[4], temp[50000] = {'\0'},depsDeps[50000] = {'\0'};
	int i,i1 = 0,i2 = 0;

     if(fp != NULL){
	  if((i = mdaIncludes(argv,"-r",argc-1,1)) != -2 || mdaIncludes(argv,"-",argc-1,1) == -2){	

	    readDeps(fp, s);
	    strcpy(temp,s);
	    fclose(fp);
	  i2 = stringify(temp,' ',deps);
	    while(i1 < i2){
	       if(!startsWith(deps[i1], "-") && !startsWith(filename,deps[i1]) && (fp = fopen(deps[i1],"r")) != NULL){
		 readDepsDeps(fp,depsDeps);
		 fclose(fp);
	       }
		    i1++;
	    }

	    if(i == -2){
		    
	  i2 = stringify(depsDeps,' ',deps);
	  i1 = 0;

	printf("%s", s);
	    while(i1 < i2){
		if(!sIncludes(s,deps[i1]) && !sIncludes(filename,deps[i1])){
		 printf("%s ",deps[i1]);
		}
		    i1++;
	    }
	    printf("%s\n",filename);
	}else{
		i1 = 0;
		if(mdaIncludes(argv,"-rv",argc-1,1) != -2){
			strcpy(temp,s);
			strcat(temp,depsDeps);
	
			i2 = stringify(temp,' ',deps);
		}
		while(i1 < i2){
		   if(!startsWith(deps[i1], "-") && !startsWith(filename,deps[i1])){
			printf("%s\n",deps[i1]);
		   }
		  i1++;
		}
	    }

	  }else if((i = mdaIncludes(argv,"-m",argc-1,1)) != -2){
		
		  if(mdaIncludes(argv,"-nodev",argc-1,1) != -2){
		  makeDeps(fp, s, argv, argc-1,i+1,0);
		  }else{
		  makeDeps(fp, s, argv, argc-1,i+1,1);
		}

		  if(mdaIncludes(argv,"-f",argc-1,1) != -2){
			fclose(fp);
		fp = fopen(filename,"w");
		fprintf(fp,"%s",s);  
			}else{
			fprintf(stdout,"This operation is potentially destructive. Do you want to proceed?\n [yes/no]\n");
        	scanf("%s", res);
     		if(sIncludes(res,"y")){
		fclose(fp);
		fp = fopen(argv[argc-1],"w");
		fprintf(fp,"%s",s);

		}
	}

		  	  }else if((i = mdaIncludes(argv,"-a",argc-1,1)) != -2){
	
		appendDeps(fp, s, argv,argc-1, i+1);
		if(mdaIncludes(argv,"-f",argc-1,1) != -2){
			fclose(fp);
		fp = fopen(argv[argc-1],"w");
		fprintf(fp,"%s",s);  
			}else{
			fprintf(stdout,"This operation is potentially destructive. Do you want to proceed?\n [yes/no]\n");
        	scanf("%s", res);
     		if(sIncludes(res,"y")){
		fclose(fp);
		fp = fopen(argv[argc-1],"w");
		fprintf(fp,"%s",s);

		}
	}

			  }else{
	    fprintf(stderr, "\033[0;31mOops! Invalid Option\n");
	  }
     }else{
	fprintf(stderr,"There is no file %s in this directory. Do you want to create a new file with this name?\n", argv[argc-1]);
	scanf("%s",res);
	  if(sIncludes(res, "y")){
	    fp = fopen(argv[argc-1], "w");
	  }
     }
    
     if(!mdaIncludes(argv,"-r",argc-1,1)){
	fclose(fp);
     }
    }
