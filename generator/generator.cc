#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#define foreach(i,a,b) for (__typeof(a) i = a; i != b; ++i)
#define forall(i,x) foreach (i, x.begin(), x.end())

#define TAM 1000
#define PENALTY 20*60

struct User {
	string id;
	string name;
	vector<int>  penalty;
	vector<int>  errors;
	int  solved;
    int  penaltySum;

    User(string i="", string n="", int numProblems=100) : id(i), name(n) {
        solved = penaltySum = 0;
        penalty = errors = vector<int>(numProblems,0);
    }

    bool operator<(const User& o) const {
        if (solved != o.solved) return solved > o.solved;
        if (penaltySum != o.penaltySum) return penaltySum < o.penaltySum;
        return name < o.name;
    }

};

typedef User Team;

char contestName[TAM];
int start, end, now;

vector<User> users;
vector<Team> teams;

vector<string> idProblems;

void error(char *msg){ printf("generator.c - %s\n", msg); }

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

void readTimeNow(){
    FILE *in = fopen("../log/now.log","r");
    char t[TAM];

    if ( in == NULL ){
        error("File ../log/now.log not found!");
        exit(1);
    }

    fgets(t,TAM,in);
    now = seconds(t);

    fclose(in);
}

void readContestInfo(){
    FILE *in = fopen("../config/contest.info","r");
    char s[TAM], e[TAM];

    if ( in == NULL ){
        error("File ../config/contest.info not found!");
        exit(1);
    }

    fgets(contestName,TAM,in);
    fgets(s,TAM,in);
    fgets(e,TAM,in);
    start = seconds(s);
    end = seconds(e);

    fclose(in);
}

void readUsers(){
    FILE *in = fopen("../config/users.info","r");

    if ( in == NULL ){
        error("File ../config/users.info not found!");
        exit(1);
    }

    if (idProblems.size() == 0) {
        error("File ../config/problems.info contains none problem!");
    }

    char id[TAM];
    char name[TAM];
    while ( fscanf(in, " %[^\n] %[^\n]", id, name) == 2) {
        users.push_back(User(id, name, idProblems.size()));
    }

    fclose(in);
}

void readTeams(){
    FILE *in = fopen("../config/teams.info","r");

    if ( in == NULL ){
        error("File ../config/teams.info not found!");
        exit(1);
    }

    if (idProblems.size() == 0) {
        error("File ../config/problems.info contains none problem!");
        exit(1);
    }

    char id[TAM];
    char name[TAM];
    while (fscanf( in, " %[^\n] %[^\n]", id, name) == 2){
        teams.push_back(Team(id, name, idProblems.size()));
    }

    fclose(in);
}

User* findUser(string id){
    forall (u, users) {
        if (u->id == id) {
            return &(*u);
        }
    }
    return NULL;
}

Team* findTeam(string id){
    forall (t, teams) {
        stringstream ss(t->id);
        for (string tid; ss >> tid;) {
            if (tid == id) {
                return &(*t);
            }
        }
    }
    return NULL;
}

void readProblems(){
    FILE *in = fopen("../config/problems.info","r");

    if ( in == NULL ){
        error("File ../config/problems.info not found!");
        exit(1);
    }

    char id[TAM];
    char link[TAM];
    while (fscanf(in, " %[^\n] %[^\n]", id, link) == 2){
        idProblems.push_back(id);
    }

    fclose(in);
}

int findProblemIndex(string id){
    for (int i = 0; i < (int)idProblems.size(); i++)
        if (id == idProblems[i]) 
            return i;
    return -1;
}

void readRuns(){
    FILE *in = fopen("../log/submitions.log","r");

    if ( in == NULL ){
        error("File ../log/submitions.log not found!");
        exit(1);
    }


    char runId[TAM];
    char runTime[TAM];
    char runUser[TAM];
    char runProblem[TAM];
    char runResult[TAM];
    while ( fscanf(in,"%s %s %s %s %s", 
                runId,
                runTime,
                runUser,
                runProblem,
                runResult) == 5 ){

        User* user = findUser(runUser);
        Team* team = findTeam(runUser);
        int prob = findProblemIndex(runProblem);

        // trata usuários
        if ( user != NULL && user->penalty[prob] == 0 ) { // ainda não acertou
            if ( !strcmp(runResult,"AC") ){
                user->penalty[prob] = seconds(runTime) - start;
                user->solved++;
                user->penaltySum += user->penalty[prob] + user->errors[prob] * PENALTY;
            }else
                user->errors[prob]++;
        }

        //trata equipes
        if (team != NULL && team->penalty[prob] == 0) { // ainda não acertou
            if ( !strcmp(runResult,"AC") ){
                team->penalty[prob] = seconds(runTime) - start;
                team->solved++;
                team->penaltySum += team->penalty[prob] + team->errors[prob] * PENALTY;
            }else
                team->errors[prob]++;
        }
    }

    fclose(in);
}

void writeLog(){
    FILE *out = fopen("../log/contest.log","w");


    fprintf(out,"%d\n", teams.size());
    fprintf(out,"%d\n", users.size());
    fprintf(out,"%d\n", idProblems.size());

    sort(teams.begin(), teams.end());
    sort(users.begin(), users.end());

    int position = 1;
    forall (t, teams){

        fprintf(out,"%d\t%s",position,t->name.c_str());
        for (int p = 0; p < (int)idProblems.size(); p++) {
            fprintf(out,"\t%d/%d", t->penalty[p],t->errors[p]);
        }
        fprintf(out,"\t%d\t%d\n", t->solved,t->penaltySum);

        if ((t+1) != teams.end() && *t < *(t+1)) ++position;
    }

    position = 1;
    forall (u, users){

        fprintf(out,"%d\t%s",position,u->name.c_str());
        for (int p = 0; p < (int)idProblems.size(); p++) {
            fprintf(out,"\t%d/%d", u->penalty[p],u->errors[p]);
        }
        fprintf(out,"\t%d\t%d\n", u->solved,u->penaltySum);

        if ((u+1) != users.end() && *u < *(u+1)) ++position;
    }

}

int main(){

    readTimeNow();
    readContestInfo();

    readProblems();
    readUsers();
    readTeams();
    readRuns();
    writeLog();

    return 0;
}

