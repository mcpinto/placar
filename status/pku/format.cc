#include <cstdio>
#include <cstring>
#define TAM 100
#define FUSO 10*60*60

char id_submissao[TAM];
char id_autor[TAM];
char id_questao[TAM];
char veredito[TAM];
char memoria[TAM];
char tempo[TAM];
char linguagem[TAM];
char data[TAM];

char* abrevia_veredito(char *v){
    if ( !strcmp(v, "Accepted") ) 				return "AC";
    if ( !strcmp(v, "Presentation Error") ) 	return "PE";
    if ( !strcmp(v, "Wrong Answer") ) 			return "WA";
    if (  strstr(v, "Runtime Error") != NULL ) 	return "RE";
    if ( !strcmp(v, "Time Limit Exceeded") )	 	return "TLE";
    if ( !strcmp(v, "Memory Limit Exceeded") )	return "MLE";
    if ( !strcmp(v, "Output Limit Exceeded") )	return "OLE";
    if ( !strcmp(v, "Compile Error") ) 			return "CE";
    if ( !strcmp(v, "Restricted Function") )	return "RF";
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
    char lixo[TAM];

    while ( !feof(stdin) ){
        scanf(" %[^\n]", id_submissao);
        scanf(" %[^\n]", id_autor);
        scanf(" %[^\n]", id_questao);
        scanf(" %[^\n]", veredito);
        //if ( !strcmp(veredito, "Accepted") ){
            scanf(" %[^\n]", memoria);
            scanf(" %[^\n]", tempo);
        //}
        scanf(" %[^\n]", linguagem);
        scanf(" %[^\n]", lixo);
        scanf(" %s", data);

        printf("%s %s %s %s %s\n",
                id_submissao,
                troca_fuso(data),
                id_autor,
                id_questao,
                abrevia_veredito(veredito));
        scanf(" "); /* lixo */
    }
    return 0;
}
