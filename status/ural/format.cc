#include <cstdio>
#include <cstring>
#define TAM 100
#define FUSO 8*60*60

char id_submissao[TAM];
char data[TAM];
char id_autor[TAM];
char nome_autor[TAM];
char id_questao[TAM];
char linguagem[TAM];
char veredito[TAM];
char tempo[TAM];
char memoria[TAM];

char* abrevia_veredito(char *v){
    if ( !strcmp(v, "Accepted") ) 				return "AC";
    if ( !strcmp(v, "Presentation error") ) 	return "PE";
    if ( !strcmp(v, "Wrong answer") ) 			return "WA";
    if (  strstr(v, "Crash") != NULL )		 	return "RE";
    if ( !strcmp(v, "Time limit exceeded") ) 	return "TLE";
    if ( !strcmp(v, "Memory limit exceeded") )	return "MLE";
    if ( !strcmp(v, "Output eimit exceeded") )	return "OLE";
    if ( !strcmp(v, "Compilation error") ) 		return "CE";
    if ( !strcmp(v, "Restricted function") )	return "RF";
    if ( !strcmp(v, "Running") ) 				return "RUNNING";
    return "OTHER";
}

char *tira_espaco(char *s){
    int i;
    for ( i = 0; *(s+i) != '\0' ; i++  )
        if ( *(s+i) == ' ' )
            *(s+i) = '-';
    return s;
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

    scanf(" %[^\n]", lixo);
    while ( !feof(stdin) ){
        scanf(" %[^\n]", id_submissao);
        scanf(" %[^\n]", data);
        scanf(" %[^\n]", id_autor);
        scanf(" %[^\n]", nome_autor);
        scanf(" %[^\n]", id_questao);
        scanf(" %[^\n]", linguagem);
        scanf(" %[^\n]", veredito);
        if ( strcmp(veredito, "Compilation error") ){
            if ( strcmp(veredito, "Accepted") )
                scanf(" %[^\n]", lixo);
            scanf(" %[^\n]", tempo);
            scanf(" %[^\n]", memoria);
        }

        printf("%s %s %s %s %s\n",		id_submissao,
                troca_fuso(data),
                id_autor,
                id_questao,
                abrevia_veredito(veredito));
        scanf(" "); /* lixo */
    }
    return 0;
}
