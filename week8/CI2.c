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

void split(char* src, char* dest[]) {	
	int i = 0;
	char* word;
	word = strtok(src, " \t");
	while (word != NULL) {
		dest[i] = word;
		i++;
		word = strtok(NULL, " \t");
	}
}

void clear(char* commands[]) {
	for (int i = 0; i < MAX_SIZE_OF_COMMAND; i++)
		commands[i] = NULL;
}

void runCommandInterpreter() {
	int status;
	while (1) {
		char command[MAX_SIZE_OF_COMMAND];
		write(1, PROMPT, PROMPT_SIZE);
		read(0, command, MAX_SIZE_OF_COMMAND);

		bool shouldExecuteInBackgroundMode = check(BACKGROUND_SYMBOL, command);

		if (shouldExecuteInBackgroundMode)
			removeChars(BACKGROUND_SYMBOL, command);

		replaceChars(NEW_LINE_SYMBOL, NULL_CHAR_SYMBOL, command);

		char* commands[MAX_SIZE_OF_COMMAND];
		clear(commands);
		split(command, commands);
		
		if (equals(commands[0], QUIT_WORD))
			return;

		if (fork() == 0) {
			if (shouldExecuteInBackgroundMode) {
				printInt(getpid());
				write(1, &NEW_LINE_SYMBOL, 1);
			}
			execvp(commands[0], commands);
			exit(-1);
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
