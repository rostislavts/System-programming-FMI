#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef int bool;
#define true 1;
#define false 0;

const char* PROMPT 				= "rostislavts $ ";
const char* QUIT_WORD 			= "exit";
const char* WRONG_CMD_MESSAGE   = "Command not found!\n";
const char 	BACKGROUND_SYMBOL 	= '&';
const char 	INTERVAL_SYMBOL 	= ' ';
const char 	TAB_SYMBOL 			= '\t';
const char 	NEW_LINE_SYMBOL 	= '\n';
const char 	NULL_CHAR_SYMBOL 	= '\0';
const char  PIPE_SYMBOL         = '|';
const int 	MAX_SIZE_OF_COMMAND = 512;
const int 	PROMPT_SIZE 		= 14;
const int 	WRONG_CMD_MSG_SIZE  = 19;

bool equals(char* str1, char* str2) {
	return !strcmp(str1, str2);
}

void removeChars(char c, char* command) {
	char result[MAX_SIZE_OF_COMMAND];
	int j = 0;
	for (int i = 0; i < strlen(command); i++)
		if (command[i] != c) {
			if (j >= MAX_SIZE_OF_COMMAND)
				break;
			result[j] = command[i];
			j++;
		}
	strncpy(command, result, j);
}

void replaceChars(char a, char b, char* command) {
	for (int i = 0; i < strlen(command); i++)
		if (command[i] == a)
			command[i] = b;
}

bool check(char c, char* command) {
	while (*command != '\0') {
		if (*command == c)
			return true;
		command++;
	}
	return false;
}

int reverseInt(int n) {
	int reversed = 0;
	while (n != 0) {
		reversed *= 10;
		reversed += n % 10;
		n /= 10;
	}
	return reversed;
}

void printInt(int n) {
	int reversed = reverseInt(n);
	char digit;
	while (reversed != 0) {
		digit = '0' + reversed % 10;
		reversed /= 10;
		write(1, &digit, 1);
	}
}

char* substr(int from, int to, char* str) {
    char* result = malloc(sizeof(char) * (to - from + 1));
    int j = 0;
    for (int i = from; i < to; i++) {
        result[j] = str[i];
        j++;
    }
    return result;
}

int split2(char* src, char* dest[]) {
    int length = strlen(src);
    char word[MAX_SIZE_OF_COMMAND];
    int k = 0;

    for (int i = 0; i < length; i++) {
        while (i < length && (src[i] == INTERVAL_SYMBOL || src[i] == TAB_SYMBOL))
            i++;

        if (i >= length)
            return k;  

        int from = i;
        while (i < length && src[i] != INTERVAL_SYMBOL && src[i] != TAB_SYMBOL)
            i++;
        
        int to = i;
        dest[k] = substr(from, to, src);
        k++;
    }
    return k;
}


void clear(char* commands[]) {
	for (int i = 0; i < MAX_SIZE_OF_COMMAND; i++)
		commands[i] = NULL;
}

void executePipe(char* commands[]) {
    int fd[2];
    pipe(fd);

    if (!fork()) { // Child process
        // Redirect stdout
        close(1);
        dup(fd[1]); // fd[1] is for write
        close(fd[0]);
        close(fd[1]);

        if (execlp(commands[0], commands[0], NULL) == -1) {
            exit(1);
        }
    } else { // Parent process
        // Redirect stdin
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        
        if(execvp(commands[1], commands + 1) == -1) {
            exit(1);
        }
    }
}

void runCommandInterpreter() {
	int status;
	while (1) {
		char command[MAX_SIZE_OF_COMMAND];
		write(1, PROMPT, PROMPT_SIZE);
		read(0, command, MAX_SIZE_OF_COMMAND);

		bool shouldExecuteInBackgroundMode = check(BACKGROUND_SYMBOL, command);
        bool hasPipe = check(PIPE_SYMBOL, command); 

		if (shouldExecuteInBackgroundMode)
			removeChars(BACKGROUND_SYMBOL, command);

        if (hasPipe) 
            removeChars(PIPE_SYMBOL, command);

		replaceChars(NEW_LINE_SYMBOL, NULL_CHAR_SYMBOL, command);

		char* commands[MAX_SIZE_OF_COMMAND];
		clear(commands);
		split2(command, commands);
		
		if (equals(commands[0], QUIT_WORD))
			return;

		if (fork() == 0) {
			if (shouldExecuteInBackgroundMode) {
				printInt(getpid());
				write(1, &NEW_LINE_SYMBOL, 1);
			}

            if (hasPipe) {
                executePipe(commands);
            } else {
    			execvp(commands[0], commands);
	    		exit(-1);
            }
		} else {
			if (!shouldExecuteInBackgroundMode)
				wait(&status);
			if (status != 0)
				write(1, WRONG_CMD_MESSAGE, WRONG_CMD_MSG_SIZE);
		}
	}
}

int main(int argc, char* argv[]) {
	runCommandInterpreter();
	return 0;
}

