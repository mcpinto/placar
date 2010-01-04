#include <cstdio>
#include <cstring>
#define TAM 100
#define FUSO 3*60*60

char id_submissao[TAM];
char data[TAM];
char id_autor[TAM];
char nome_autor[TAM];
char id_questao[TAM];
char nome_questao[TAM];
char veredito[TAM];
char tempo[TAM];
char memoria[TAM];
char linguagem[TAM];

char* abrevia_veredito(char *v){
    if ( !strcmp(v, "accepted") ) 				return "AC";
    if ( !strcmp(v, "presentation error") ) 	return "PE";
    if ( !strcmp(v, "wrong answer") ) 			return "WA";
    if ( strstr(v, "runtime error") != NULL ) 	return "RE";
    if ( !strcmp(v, "time limit exceeded") ) 	return "TLE";
    if ( !strcmp(v, "memory limit exceeded") )	return "MLE";
    if ( !strcmp(v, "output limit exceeded") )	return "OLE";
    if ( !strcmp(v, "compilation error") )		return "CE";
    if ( !strcmp(v, "restricted function") )	return "RF";
    if ( strstr(veredito, "running") != NULL )	return "RUNNING";
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
        scanf(" %s", data);
        scanf(" %[^\n]", id_autor);
        scanf(" %[^\n]", nome_autor);
        scanf(" %[^\n]", id_questao);
        scanf(" %[^\n]", nome_questao);
        scanf(" %[^\n]", lixo);
        scanf(" %[^\n]", veredito);
        //if ( strstr(veredito, "runtime error") != NULL 
        //        || strstr(veredito, "running") != NULL ) scanf(" %[^\n]", lixo);
        scanf(" %[^\n]", tempo);
        scanf(" %[^\n]", memoria);
        scanf(" %[^\n]", linguagem);

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
