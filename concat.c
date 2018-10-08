/****
-o concat
strings.c
#*/
#include <stdio.h>

int concat(char s[], char *strings[], int len){
extern int strCopy(char s[], char t[], int cont);
int i, i1;

	for(i = i1 = 0; i < len; i++){
	 i1 = strCopy(s, strings[i], i1);
	}
	s[i1] = '\0';
	return i1;
}

/**int main(int argc, char **argv){
int c, i;
char str[500] = "Sheriff", a[] = " Mobolaji", b[] = " Esseson", *mda[] = {" Mobolaji", " Esseson", " Osiqueme", " smeO"}, *p = str, **pp = &p;
        concat(str,mda, 4);
	printf("%s\n", str);

}**/
