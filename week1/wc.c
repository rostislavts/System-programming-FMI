#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

// wc [-cwl] [f1 ... fn]

bool checkForOption(char* argv[]) {
	return argv[2][0] == '-';
}

void raiseNeededFlags(char* argv[], bool* shouldCountLines, bool* shouldCountWords, bool* shouldCountChars) {
	char* p = argv[2];
	int len = 0;
	while (p[len])
		len++;

	for (int i = 1; i < len; i++) {
		if (argv[2][i] == 'l')
			*shouldCountLines = true;
		else if (argv[2][i] == 'w')
			*shouldCountWords = true;
		else if (argv[2][i] == 'c')
			*shouldCountChars = true;
	}
}

int main(int argc, char* argv[]) {

	int words = 0, lines = 0, chars = 0;

	const int MAX_SIZE_OF_FDS = 50;
	int idxOfFirstFileNameInArgv = -1;
	int usedFds = 0; // <= MAX_SIZE_OF_FDS
	int fds[MAX_SIZE_OF_FDS];

	bool shouldCountLines = false, shouldCountWords = false, shouldCountChars = false;
	
	if (argc == 2) { // read from stdin and count words, lines and chars
		idxOfFirstFileNameInArgv = -1;
		usedFds = 1;
		fds[0] = 0; // stdin	

		shouldCountChars = shouldCountWords = shouldCountLines = true;

	} else if (argc == 3 && checkForOption(argv)) {
		raiseNeededFlags(argv, &shouldCountLines, &shouldCountWords, &shouldCountChars);
		usedFds = 1;
		fds[0] = 0;
	} else { 

		bool hasOption = checkForOption(argv);

		if (hasOption) {
			raiseNeededFlags(argv, &shouldCountLines, &shouldCountWords, &shouldCountChars);
			idxOfFirstFileNameInArgv = 2; 
		} else {
			idxOfFirstFileNameInArgv = 1;
			shouldCountChars = shouldCountWords = shouldCountLines = true;
		}

		int j = 0;
		for (int i = idxOfFirstFileNameInArgv; i < argc; i++) {
			fds[j] = open(argv[i], O_RDONLY);
			if (fds[j] != -1) // is valid
				j++;
		}

		usedFds = argc - idxOfFirstFileNameInArgv - 1;
	} 

	// logic part
	for (int i = 0; i < usedFds; i++) {
		int c;
		const int MAX_SIZE_OF_BUFF = 512;
		char buff[MAX_SIZE_OF_BUFF];

		while(c = read(fds[i], buff, MAX_SIZE_OF_BUFF)) {
			chars += c;
			for (int j = 0; j < c; j++) {
				if (buff[j] == '\n') {
					lines++;
					words++;
				}
				else if (buff[j] == ' ')
					words++;
			}
		}
	}

	if (shouldCountLines)
		printf("\t%d", lines);

	if (shouldCountWords)
		printf("\t%d", words);

	if (shouldCountChars)
		printf("\t%d", chars);

	printf("\n");

	for (int i = 0; i < usedFds; i++) {
		close(fds[i]);
	}

	return 0;
}