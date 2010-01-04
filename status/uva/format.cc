#include <cstdio>
#include <cstring>
#include <cctype>
#define TAM 100
#define FUSO 2*60*60

char id_submissao[TAM];
char data[TAM]; /* em segudos deste 1970*/
char veredito[TAM];
char tempo[TAM];
char memoria[TAM];
char id_autor[TAM];
char nome_autor[TAM];
char linguagem[TAM];
char id_questao[TAM];
char nome_questao[TAM];

char* abrevia_veredito(char *v){
	if ( !strcmp(v, "Accepted") ) 				return "AC";
	if ( strstr(v, "Presentation error") != NULL) 	return "PE";
	if ( strstr(v, "Wrong answer") != NULL) 			return "WA";
	if (  strstr(v, "Runtime error") != NULL ) 	return "RE";
	if ( !strcmp(v, "Time limit exceeded") ) 	return "TLE";
	if ( !strcmp(v, "Memory limit exceeded") )	return "MLE";
	if ( !strcmp(v, "Output limit exceeded") )	return "OLE";
	if ( !strcmp(v, "Compilation error") ) 			return "CE";
	if ( !strcmp(v, "Restricted function") )	return "RF";
	if ( !strcmp(v, "Received") ) 				return "RUNNING";
	return "OTHER";
}

char *troca_fuso(char *d){
	int s;
	sscanf(d,"%d", &s);
	s -= FUSO;
	sprintf(d,"%d",s);
	return d;
}

int main(){

	while ( !feof(stdin) ){
		scanf(" %[^\n]", id_submissao);
		scanf(" %[^\n]", id_questao);
		scanf(" %[^\n]", nome_questao);
		scanf(" %[^\n]", id_autor);
		scanf(" %[^\n]", nome_autor);
		scanf(" %[^\n]", veredito);
		scanf(" %[^\n]", linguagem);
		scanf(" %[^\n]", tempo);
		scanf(" %[^\n]", data);

		if(!isdigit(id_submissao[0])) continue;
		printf("%s %s %s %s %s\n",	id_submissao,
										troca_fuso(data),
										id_autor,
										id_questao,
										abrevia_veredito(veredito));
		scanf(" "); /* lixo */
	}
	return 0;
}
