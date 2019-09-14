#include <interpreter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>

static char *interpret_private(const char *in, int lo) {
    int c = 0;
    int loop = lo;
    size_t p = 0,len = 0, iter = 0;
    char *buf = NULL, *buf2 = NULL, *g = NULL;
    buf = readline(in);
    if(!buf) {
        return NULL;
    }
    while((c = buf[p]) != '\0') {
        if(c == '[') {
            ++loop;
        } else if(c == ']') {
            --loop;
        }
        ++p;
    }
    if(loop > 0) { /* unbalanced loop. */
        buf2 = interpret_private("... ", loop);
        if(buf2 == NULL) {
            free(buf);
            return NULL;
        }
        len = strlen(buf2);
        iter = 0;
        g = realloc(buf, sizeof(*buf) * (p + len + 2));
        if(!g) {
            printf("fatal error: not enough memory.\n");
            free(buf);
            free(buf2);
            return NULL;
        }
        buf = g;

        while(iter < len) {
            buf[p + iter] = buf2[iter];
            ++iter;
        }
        p += iter;
    }
    buf[p] = '\0';
    return buf;
}

char *interpret() {
    return interpret_private(">> ", 0);
}
