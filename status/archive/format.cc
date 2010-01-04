#include <cstdio>
#include <cstring>
#define TAM 100
#define FUSO 2*60*60

char id_submissao[TAM];
char data[TAM];
char veredito[TAM];
char tempo[TAM];
char memoria[TAM];
char id_autor[TAM];
char linguagem[TAM];
char id_questao[TAM];
char nome_questao[TAM];

char* abrevia_veredito(char *v){
    if ( !strcmp(v, "Accepted") ) 				return "AC";
    if ( !strcmp(v, "Presentation Error") ) 	return "PE";
    if ( !strcmp(v, "Wrong Answer") ) 			return "WA";
    if (  strstr(v, "Runtime Error") != NULL ) 	return "RE";
    if ( !strcmp(v, "Time Limit Exceeded") ) 	return "TLE";
    if ( !strcmp(v, "Memory Limit Exceeded") )	return "MLE";
    if ( !strcmp(v, "Output Limit Exceeded") )	return "OLE";
    if ( !strcmp(v, "Compile Error") ) 			return "CE";
    if ( !strcmp(v, "Restricted Function") )	return "RF";
    if ( !strcmp(v, "Received") ) 				return "RUNNING";
    return "OTHER";
}

char *troca_fuso(char *d){
    int s;
    sscanf(d, "%d", &s);
    s -= FUSO;
    sprintf(d, "%d", s);
    return d;
}

int main(){
	int cnt = 0;
    while ( !feof(stdin) ){
        scanf(" %s", id_submissao);
        scanf(" %s", data);
        scanf(" %[^\n]", veredito);
        scanf(" %s", tempo);
        scanf(" %s", memoria);
        scanf(" %s", id_autor);
        scanf(" %s", linguagem);
        scanf(" %s", id_questao);
        scanf(" %[^\n]", nome_questao);

        printf("%s %s %s %s %s\n",
                id_submissao,
                troca_fuso(data),
                id_autor,
                id_questao,
                abrevia_veredito(veredito));
        scanf(" "); /* lixo */
	if (cnt++ > 10) break;
    }
    return 0;
}
