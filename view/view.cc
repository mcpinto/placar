#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

#define TAM 1000

struct User {
    int pos;
    string name;
    vector<int> penalty;
    vector<int> errors;
    int solved;
    int penaltySum;
};

typedef User Team;

struct Problem {
    string id;
    string link;
};

char contestName[TAM];
int startTime, endTime, timeNow, remainTime;
char start[TAM];
char end[TAM];
char now[TAM];
char remain[TAM];

int nTeams;
vector<Team> teams;

int nUsers;
vector<User> users;

int nProblems;
vector<Problem> problems;

void error(char *msg){ printf("view.c - %s\n", msg); }

void readProblems(){
    FILE *in = fopen("../config/problems.info","r");

    problems.resize(nProblems);

    char id[TAM];
    char link[TAM];
    for (int i = 0; i < nProblems; i++ ){
        fscanf(in, " %[^\n]", id);
        fscanf(in, " %[^\n]", link);
        problems[i].id = id;
        problems[i].link = link;
    }

    fclose(in);
}


int seconds(char *t){
    int s;
    if(strstr(t,"-") != NULL){
        char cmd[TAM];
        strcpy(cmd,"date -d \"");
        strcat(cmd,t);
        strcat(cmd,"\" +%s > /tmp/_asdf_");
        system(cmd);

        FILE* in = fopen("/tmp/_asdf_","r");
        fscanf(in,"%d",&s);
        fclose(in);
        return s;
    }
    sscanf(t, "%d",&s);
    return s;
}

char *format(char *t, int sec){
    /*int h,m,s;
    s = sec % 60;
    m = (sec / 60) % 60;
    h = sec / 3600;
    sprintf(t, "%02d:%02d:%02d", h,m,s);*/
    int min = sec / 60;
    sprintf(t, "%d", min);
    return t;
}

void readTimeNow(){
    FILE *in = fopen("../log/now.log","r");
    if ( in == NULL ){
        error("File ../log/now.log not found!");
        exit(1);
    }
    fgets(now,TAM,in);
    timeNow = seconds(now);
    remainTime = endTime - timeNow;
    format(remain,remainTime);
    fclose(in);
}

void readContestInfo(){
    FILE *in = fopen("../config/contest.info","r");

    if ( in == NULL ){
        error("File ../config/contest.info not found!");
        exit(1);
    }

    fgets(contestName,TAM,in);
    fgets(start,TAM,in);
    fgets(end,TAM,in);
    startTime = seconds(start);
    endTime = seconds(end);

    fclose(in);
}

void readlog(){
    FILE *in = fopen("../log/contest.log","r");

    if ( in == NULL ){
        error("File ../log/contest.log not found!");
        exit(1);
    }

    fscanf(in,"%d", &nTeams);
    fscanf(in,"%d", &nUsers);
    fscanf(in,"%d", &nProblems);

    teams.resize(nTeams);
    users.resize(nUsers);

    char name[TAM];

    for (int t = 0; t < nTeams; t++) {
        fscanf(in, "%d\t",&teams[t].pos);
        fscanf(in, "%[^\t]",name);
        teams[t].name = name;

        teams[t].penalty.resize(nProblems);
        teams[t].errors.resize(nProblems);

        for (int p = 0; p < nProblems; p++) {
            fscanf(in, "\t%d/%d", &teams[t].penalty[p],&teams[t].errors[p]);
        }

        fscanf(in, "\t%d\t%d\n", &teams[t].solved,&teams[t].penaltySum);
    }


    for (int u = 0; u < nUsers; u++) {
        fscanf(in, "%d\t",&users[u].pos);
        fscanf(in, "%[^\t]",name);
        users[u].name = name;

        users[u].penalty.resize(nProblems);
        users[u].errors.resize(nProblems);

        for (int p = 0; p < nProblems; p++) {
            fscanf(in, "\t%d/%d", &users[u].penalty[p],&users[u].errors[p]);
        }

        fscanf(in, "\t%d\t%d\n", &users[u].solved,&users[u].penaltySum);
    }

    fclose(in);
}

int printContestInfo (FILE *p) {
    int started = 1;

    fprintf(p, "\n\n<table class=header><tr><td><h1>%s</h1></td></tr></table>\n", contestName);

    fprintf(p, "<p></p>\n");


    fprintf(p, "<table class=info><tr><td>\n<h4>");

    fprintf (p, "<p> Start : %s / End : %s / Now : %s</p>\n", start,end,now);

    if ( timeNow >= endTime)
        fprintf (p, "Contest Finished!\n");
    else if ( timeNow < startTime ) {
        char tmp[TAM];
        fprintf (p, "Contest starts in %s!\n", format(tmp,startTime - timeNow));
        started = 0;
    } else
        fprintf (p, "Remaining Time - %s\n", remain);

    fprintf(p, "</h4>\n</td></tr></table>\n\n");

    return started;
}

void styleCss(FILE* p) {
    fprintf(p,"\n\n<style type=\"text/css\">\n");
    FILE *css = fopen("style.css","r");
    if (css != NULL) {
        char line[TAM];
        while (fgets(line, TAM, css)) fprintf(p, "%s\n", line);
    }
    fprintf(p,"</style>\n\n");
}

void preHtml(FILE* p) {
    fprintf(p, "<html>\n<head>\n<title>%s</title>\n",contestName);
    fprintf(p, "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' >\n");
    fprintf(p, "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"30; URL=\">\n");
    styleCss(p);
    fprintf(p, "</head>\n<body>\n");
}

void posHtml(FILE* p) {
    fprintf (p, "<p></p><p></p>\n");
    fprintf (p, "<table class=footer><tr><td>By Joel Uchoa (Tsebayoth)</td></tr></table>\n");
    fprintf (p, "</body>\n</html>\n");
}

void rankHead(FILE *p, char *part, int started) {
    fprintf(p, "<tr class=headerrow abgcolor=\"#00AFDF\">\n");
    fprintf(p, "<td/><td width=250><b>%s</b></td>\n", part);
    for (int i = 0; i < nProblems; i++) {
        const char *link = started ? problems[i].link.c_str() : "";
        const char *id = started ?  problems[i].id.c_str() : "???";
        fprintf (p, "<td><b><a href=\"%s\">%s</a></b></td>\n", link, id);
    }
    fprintf(p, "<td><b>Solved</b></td>\n");
    fprintf(p, "<td><b>Time</b></td></tr>\n");

}

void writeRank(FILE* p, char *nome, int started, vector<User>& elems) {
    char aux[TAM];

    rankHead(p, nome, started);

    for (int i = 0; i < (int)elems.size(); i++) {

        fprintf(p, "<tr class=problemrow>\n");

        fprintf(p, "<td class=teamposition abgcolor='#00AFDF'>%d</td>", elems[i].pos); //posicao
        fprintf(p, "<td class=teamname>%s</td>\n", elems[i].name.c_str()); //nome 

        for (int j = 0; j < nProblems; j++) {

            fprintf (p, "<td>");

            if (elems[i].penalty[j] > 0) { // pelalidade
                format(aux,elems[i].penalty[j]);
                fprintf(p, "<font class=ac>%s</font> ", aux);
            } else {
                fprintf(p, "0 ");
            }


            if ( elems[i].errors[j] > 0 ) {
                fprintf(p, "(<font class=error>%d</font>)", elems[i].errors[j]); /* erros */
            } else {
                fprintf(p, "(0)");
            }

            fprintf(p, "</td>\n");
        }
        fprintf (p, "<td>%d</td>\n", elems[i].solved);
        fprintf (p, "<td>%s</td>\n</tr>\n", 
                format(aux,elems[i].penaltySum));
    }

}

void writeTable(FILE *p) {
    int started;

    started = printContestInfo(p);

    fprintf(p, "<p></p>\n");
    fprintf(p, "<table class=table abgcolor=\"#8FDFFF\" >\n");

    writeRank(p, "Teams", started, teams);

    fprintf(p, "<tr><td><br/></td></tr>\n");

    writeRank(p, "Users", started, users);

    fprintf (p, "</table>\n</center>\n");
}

void writehtml(){
    FILE *out = fopen("../contest.html","w");

    preHtml(out);
    writeTable(out);
    posHtml(out);

    fclose(out);
}

int main(){

    readContestInfo();
    readTimeNow();
    readlog();
    readProblems();
    writehtml();

    return 0;
}

