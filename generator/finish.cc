#include <string.h>
#include <stdio.h>

int main(int nargs, char **args){
	int n,e;
	sscanf(args[1],"%d",&n);
	sscanf(args[2],"%d",&e);
	return n > e;
}
