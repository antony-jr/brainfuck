#include <stdlib.h>
#include <parser.h>
#include <executor.h>
#include <stdio.h>

static void readloop(char **r, size_t *p, size_t *aval){
	int c = 0;
	char *g = NULL;
	while((c = getchar()) != EOF && c != ']'){
		if(c == '\n'){
			printf("... ");
			continue;
		}	
		(*r)[(*p)++] = c;
		if((*r)[(*p)-1] == '['){
			readloop(r, p, aval);
		}	
		if(*p >= *aval){
			*aval *= 2;
			g = realloc(*r, sizeof(**r) * (*aval));
			if(!g){
				printf("fatal error: not enough memory.\n");
				free(*r);
				return;
			}
			*r = g;
		}
	}
	(*r)[(*p)++] = ']';
	(*r)[(*p)] = '\0';
	return;
}

static char *readline(const char *input){
	int c = 0;
	size_t p = 0,aval = 1024;
	char *r = calloc(aval, sizeof *r),
	     *g = NULL;
	if(!r){
		printf("fatal error: not enough memory.\n");
		return NULL;
	}
	printf("%s", input);
	while((c = getchar()) != EOF && c != '\n'){
		r[p++] = c;
		if(r[p-1] == '['){
			readloop(&r , &p, &aval);	
		}
		if(p >= aval){
			aval *= 2;
			g = realloc(r, sizeof(*r) * aval);
			if(!g){
				printf("fatal error: not enough memory.\n");
				free(r);
				return NULL;
			}
			r = g;
		}
	}
	if(c == EOF){
		free(r);
		return NULL;
	}
	r[p] = '\0';
	return r;
}

int main(int ac, char **av) {
   int *parsed = NULL;
   char *buf = NULL; 
   if(ac == 1) {
        printf(
	"Brainfuck 0.0.1 (%s, %s)\n",
	__DATE__,__TIME__
	);
	printf(
	"Copyright (C) 2019, Antony J.r.\n"
	);
	while(1){
		if(!(buf = readline(">> "))){
			putchar('\n');
			break;
		}
		parsed = parse_str(buf);
		exec(parsed);
		free(parsed);
		free(buf);
	}
	return 0;
    }
    FILE *fp = fopen(av[1], "r");
    if(!fp) {
	printf("fatal error: cannot open file.\n");
	return -1;
    }
    parsed = parse_file(fp);
    exec(parsed);
    free(parsed);
    fclose(fp);
    return 0;
}
