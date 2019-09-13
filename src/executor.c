#include <executor.h>
#include <parser.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>

#define LIMIT TAPE_SIZE-1
static uint8_t tape[TAPE_SIZE] = {0}; 


int exec(int *inst){
	int iter = 0;
	int pos = 0;
	if(!inst){
		return 0;
	}
	while(inst[iter] != END_OF_INSTRUCTIONS){
		switch(inst[iter]){
			case SET_CELL:
				tape[pos] += inst[iter + 1];
				break;
			case SET_POS:
				pos += inst[iter + 1];
				if(pos > LIMIT){
					pos = pos % TAPE_SIZE;
				}else if(pos < 0){
					pos = -pos;
					pos = TAPE_SIZE - (pos % TAPE_SIZE);
				}
				break;	
			case OPEN_LOOP:
				if(tape[pos] == 0){
					iter += inst[iter + 1];
				}
				break;
			case CLOSE_LOOP:
				if(tape[pos] != 0){
					iter -= inst[iter + 1];
				}
				break;
			case PRINT_CELL:
				write(STDOUT_FILENO, tape + pos, 1); 
				break;
			case GET_CELL:
				read(STDIN_FILENO, tape + pos, 1);
				break;	
			default:
				break;
		}
		iter += 2;
	}
	free(inst);
	return 0;
}