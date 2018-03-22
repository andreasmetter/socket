#include "myLibs.hpp"


/*
Concat:
char* concat(char*s1, char*s2){
	char* ret = (cvhar*) malloc((1+strlen(s1)+strlen(s2))*sizeof(char));
	char* tmp = ret;
	for(;*tmp=*s1;s1++;tmp++){} si copia e ci chiediamo cosa abbiamo copiato
	for(;*tmp=*s2;s2++;tmp++){}
	return ret;}
	
s = concat("Hello", "world");
s = concat(s, "prova");
Nel codice è sbagliata la strcat	
*/