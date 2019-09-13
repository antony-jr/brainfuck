#include <stdlib.h>
#include <parser.h>
#include <executor.h>
#include <stdio.h>

int main(int ac, char **av){
	if(ac == 1){
		return 0;
	}
	FILE *fp = fopen(av[1], "r");
	if(!fp){
		perror("cannot open file!");
		return -1;
	}
	exec(parse_file(fp));
	fclose(fp);
	return 0;
}
