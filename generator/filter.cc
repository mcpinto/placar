#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define foreach(i,a,b) for (__typeof(a) i = a; i != b; ++i)
#define forall(i,x) foreach(i, x.begin(), x.end())

#define TAM 10000

struct Run {
    string id;
    string time;
    string user;
    string problem;
    string result;

    Run(string i="", string t="", string u="", string p="", string r="") 
        : id(i), time(t), user(u), problem(p), result(r) {}

    bool operator<(const Run& o) const {
        int nid,nidO;
        sscanf(id.c_str(),"%d",&nid);
        sscanf(o.id.c_str(),"%d",&nidO);
        return nid < nidO;
    }

    bool operator==(const Run& o) const { return id == o.id; }
};

vector<string> idUsers;
vector<string> idProblems;
vector<Run> runs;

void error(char *msg) { printf("filter.c - %s\n", msg); }

void readUsers() {
    FILE *in = fopen("../config/users.info","r");
    char id[TAM], name[TAM];

    if (in == NULL) {
        error("File ../config/users.info not found!");
        exit(1);
    }

    while (fscanf(in, " %[^\n] %[^\n]", id, name) == 2) {
        idUsers.push_back(id);
    }

    fclose(in);
}

bool isUserInTheContest(string id) {
    forall (i, idUsers) {
        if (id == *i) {
            return true;
        }
    }
    return false;
}

void readProblems() {
    FILE *in = fopen("../config/problems.info","r");
    char id[TAM];
    char link[TAM];

    if (in == NULL) {
        error("File ../config/problems.info not found!");
        exit(1);
    }

    while (fscanf(in, " %[^\n] %[^\n]", id, link) == 2) {
        idProblems.push_back(id);
    }

    fclose(in);
}

bool isProblemInTheContest(string id) {
    forall (i, idProblems) {
        if (id == *i) {
            return true;
        }
    }
    return false;
}

void readRuns() {
    FILE *in = fopen("../log/submitions.log","r");

    if (in == NULL) {
        error("File ../log/submitions.log not found!");
        exit(1);
    }

    char id[TAM];
    char time[TAM];
    char user[TAM];
    char problem[TAM];
    char result[TAM];

    while (fscanf(in,"%s %s %s %s %s", id, time, user, problem, result) == 5) {

        if (!strcmp(result,"OTHER") || !strcmp(result,"RUNNING"))
            continue;

        runs.push_back(Run(id,time,user,problem,result));
    }

    fclose(in);
}

int isValidRun(Run& r) {
    return isUserInTheContest(r.user) && isProblemInTheContest(r.problem);
}

void writeValidRuns() {
    FILE *out = fopen("../log/submitions.log","w");

    sort(runs.begin(), runs.end());
    runs.erase(unique(runs.begin(), runs.end()), runs.end());

    forall (r, runs) {
        if (isValidRun(*r)) {
            fprintf(out, "%s %s %s %s %s\n", 
                    r->id.c_str(), 
                    r->time.c_str(), 
                    r->user.c_str(), 
                    r->problem.c_str(), 
                    r->result.c_str());
        }
    }
    fclose(out);
}

int main() {

    readUsers();
    readProblems();
    readRuns();
    writeValidRuns();

    return 0;
}

