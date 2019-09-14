#include <parser.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1048576 /* 1 MiB */
int *parse_str(const char *code) {
    int *r = calloc(BUF_SIZE, sizeof *r),
         *g = NULL;
    int aval = BUF_SIZE-1;
    char c = 0;
    int pos = 0,buf = 0,used = 0;
    stack_make_empty();
    while((c = *code++) != '\0' ) {
        if(c != '+' &&
                c != '-' &&
                c != '<' &&
                c != '>' &&
                c != '[' &&
                c != ']' &&
                c != ',' &&
                c != '.') {
            continue;
        }
        if(used >= aval) {
            /* TODO: find an optimal buffer size large enough so that we can seldom
            *       this reallocation. */
            aval = used * 4;
            g = realloc(r, (sizeof(*r))*aval);
            if(!g) {
                printf("fatal error: not enough memory.\n");
                free(r);
                return NULL;
            }
            r = g;
        }
        switch(c) {
        case '+':
            if(r[pos] == SET_CELL) {
                ++r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_CELL;
            r[pos + 1] = 1;
            used += 4;
            break;
        case '-':
            if(r[pos] == SET_CELL) {
                --r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_CELL;
            r[pos + 1] = -1;
            used += 4;
            break;
        case '<':
            if(r[pos] == SET_POS) {
                --r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_POS;
            r[pos + 1] = -1;
            used += 4;
            break;
        case '>':
            if(r[pos] == SET_POS) {
                ++r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_POS;
            r[pos + 1] = 1;
            used += 4;
            break;
        case '[':
            r[(pos += 2)] = OPEN_LOOP;
            used += 4;
            if(stack_push(pos)) {
                printf("fatal error: maximum loop depth reached.\n");
                free(r);
                return NULL;
            }
            break;
        case ']':
            if(stack_pop(&buf)) {
                printf("fatal error: unbalanced loop.\n");
                free(r);
                return NULL;
            }
            r[(pos += 2)] = CLOSE_LOOP;
            used += 4;
            r[pos + 1] = r[buf + 1] = pos - buf;
            break;
        case '.':
            if(r[pos] == PRINT_CELL) {
                ++r[pos + 1];
		continue;
	    }
            r[(pos += 2)] = PRINT_CELL;
            r[pos + 1] = 1;
            used += 4;
            break;
        case ',':
            if(r[pos] == GET_CELL) {
                ++r[pos + 1];
		continue;
            }
            r[(pos += 2)] = GET_CELL;
            r[pos + 1] = 1;
            used += 4;
            break;
        default:
            break;
        }

    }
    return r;
}



int *parse_file(FILE *fp) {

    int *r = calloc(BUF_SIZE, sizeof *r),
         *g = NULL;
    int aval = BUF_SIZE-1,used = 0;
    int c = 0;
    int pos = 0,buf = 0;
    stack_make_empty();
    rewind(fp);
    while((c = getc(fp)) != EOF) {
        if(c != '+' &&
                c != '-' &&
                c != '<' &&
                c != '>' &&
                c != '[' &&
                c != ']' &&
                c != ',' &&
                c != '.') {
            continue;
        }
        if(used >= aval) {
            aval = used * 4;
            g = realloc(r, (sizeof(*r))*aval);
            if(!g) {
                printf("fatal error: not enough memory.\n");
                free(r);
                return NULL;
            }
            r = g;
        }
        switch(c) {
        case '+':
            if(r[pos] == SET_CELL) {
                ++r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_CELL;
            r[pos + 1] = 1;
            used += 4;
            break;
        case '-':
            if(r[pos] == SET_CELL) {
                --r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_CELL;
            r[pos + 1] = -1;
            used += 4;
            break;
        case '<':
            if(r[pos] == SET_POS) {
                --r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_POS;
            r[pos + 1] = -1;
            used += 4;
            break;
        case '>':
            if(r[pos] == SET_POS) {
                ++r[pos+1];
                continue;
            }
            r[(pos += 2)] = SET_POS;
            r[pos + 1] = 1;
            used += 4;
            break;
        case '[':
            r[(pos += 2)] = OPEN_LOOP;
            used += 4;
            if(stack_push(pos)) {
                printf("fatal error: maximum loop depth reached.\n");
                free(r);
                return NULL;
            }
            break;
        case ']':
            if(stack_pop(&buf)) {
                printf("fatal error: unbalanced loop.\n");
                free(r);
                return NULL;
            }
            r[(pos += 2)] = CLOSE_LOOP;
            used += 4;
            r[pos + 1] = r[buf + 1] = pos - buf;
            break;
        case '.':
            if(r[pos] == PRINT_CELL) {
                ++r[pos + 1];
		continue;
            }
            r[(pos += 2)] = PRINT_CELL;
            r[pos + 1] = 1;
            used += 4;
            break;
        case ',':
            if(r[pos] == GET_CELL) {
                ++r[pos + 1];
		continue;
            }
            r[(pos += 2)] = GET_CELL;
            r[pos + 1] = 1;
            used += 4;
            break;
        default:
            break;
        }
    }
    return r;
}
