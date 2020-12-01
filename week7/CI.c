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

const char* PROMPT = "rostislavts $ ";
const char* QUIT_WORD = "exit";
const int MAX_SIZE_OF_COMMAND = 512;
const int PROMPT_SIZE = 14;

bool equals(char* str1, char* str2) {
	return !strcmp(str1, str2);
}

void removeIntervals(char* command) {
	char result[MAX_SIZE_OF_COMMAND];
	int j = 0;
	for (int i = 0; i < strlen(command); i++)
		if (command[i] != ' ' && command[i] != '\t') {
			if (j >= MAX_SIZE_OF_COMMAND)
				break;
			result[j] = command[i];
			j++;
		}
	strncpy(command, result, j);
}

void replaceNewLineWithNullChar(char* command) {
	for (int i = 0; i < strlen(command); i++)
		if (command[i] == '\n')
			command[i] = '\0';
}


void runCommandInterpreter() {
	int status;
	while (1) {
		char command[MAX_SIZE_OF_COMMAND];
		printf("%s", PROMPT);
		scanf("%s", command); 
		if (equals(command, QUIT_WORD))
			break;
		removeIntervals(command);
		replaceNewLineWithNullChar(command);

		if (fork() == 0) {
			execlp(command, command, NULL);
			exit(-1);
		} else {
			wait(&status);
			if (status != 0)
				printf("%s\n", "Command not found!");
		}
	}

}

int main(int argc, char* argv[]) {
	runCommandInterpreter();
	return 0;
}
