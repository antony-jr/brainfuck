#include <stdlib.h>
#include <parser.h>
#include <executor.h>
#include <interpreter.h>
#include <stdio.h>
#include <editline/readline.h>

int main(int ac, char **av) {
    int *parsed = NULL;
    char *buf = NULL;
    if(ac == 1) {
#ifndef GIT_COMMIT_STR
        printf(
            "Brainfuck (%s, %s)\n",
            __DATE__,__TIME__
        );
#else
        printf(
            "Brainfuck git-commit %s (%s, %s)\n",
            GIT_COMMIT_STR,__DATE__,__TIME__
        );
#endif /* GIT_COMMIT_STR */
        printf(
            "Copyright (C) 2019, Antony J.r.\n"
        );
        while(1) {
            if(!(buf = interpret())) {
                putchar('\n');
                break;
            }
            add_history(buf);
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
