#include <parser.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int *parse_str(const char *code, size_t len){
	int *r = calloc(len*2, sizeof *r);
	char c = 0;
	int pos = -2,buf = 0;
	stack_make_empty();
	while(len){
		c = *code++;	
		--len;	
		switch(c){
			case '+':
				if(r[pos] == SET_CELL){
					++r[pos+1];
					continue;
				}
				r[(pos += 2)] = SET_CELL;
			        r[pos + 1] = 1;	
				break;
			case '-':
				if(r[pos] == SET_CELL){
					--r[pos+1];
					continue;
				}
				r[(pos += 2)] = SET_CELL;
			        r[pos + 1] = -1;	
				break;	
			case '<':
				
				if(r[pos] == SET_POS){
					--r[pos+1];
					continue;
				}
				r[(pos += 2)] = SET_POS;
				r[pos + 1] = -1;
				break;
			case '>':
				if(r[pos] == SET_POS){
					++r[pos+1];
					continue;
				}
				r[(pos += 2)] = SET_POS;
				r[pos + 1] = 1;
				break;	
			case '[':
				r[(pos += 2)] = OPEN_LOOP;
				if(stack_push(pos)){
					perror("stack overflow!");
					free(r);
					return NULL;
				}
				break;
			case ']':
				if(stack_pop(&buf)){
					perror("stack empty! unbalanced loops maybe.");
					free(r);
					return NULL;
				}
				r[(pos += 2)] = CLOSE_LOOP;
				r[pos + 1] = r[buf + 1] = pos - buf;
				break;
			case '.':
				if(r[pos] == PRINT_CELL){
					++r[pos + 1];
				}
				r[(pos += 2)] = PRINT_CELL;
				r[pos + 1] = 1;
				break;
			case ',':
				if(r[pos] == GET_CELL){
					++r[pos + 1];
				}
				r[(pos += 2)] = GET_CELL;
				r[pos + 1] = 1;
				break;	
			default:
				break;
	}

	}
	return r;
}



int *parse_file(FILE *fp){
	int c = 0;
	int *r = NULL;
	char *buf = calloc(BUF_SIZE, sizeof *buf),
	     *g = NULL;
	size_t used = 0,aval=BUF_SIZE-1;
	rewind(fp);
	while((c = getc(fp)) != EOF){
		buf[used++] = c;
		if(used >= aval){
			aval *= 2;
			g = realloc(buf, sizeof(*buf) * aval);
			if(!g){
				free(buf);
				return NULL;
			}
			buf = g;
		}
	}
	r = parse_str(buf, used);
	free(buf);
	return r;
}
