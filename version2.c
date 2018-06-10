#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80
int main(void)
{
	char *args[MAX_LINE/2 +1];
	int should_run = 1;

	char quit[50] = { 'q','u','i','t','\n' };
	char history[50] = { 'h','i','s','t','o','r','y','\n' };
	char word[50] = { 0 };
	char historyOfCommands[10][50];
	int commandCount = 0;
	int count = 0;

	while (should_run) {
		if(strcmp(word, quit) != 0){
			should_run = 0;
		}
		printf("CSCI3120>");
		fflush(stdout);
		fgets(word, 50, stdin);
		count = commandCount % 10;
		if (word[0] != '\0') {
			printf("%s\n", word);

			// TODO: History commands that will access past commands and past commands will replace Word. Word to be tokenized later.
			if (word[0] == '!') {
				if(commandCount == 0){
					printf("No Commands in History");
				}
				else if(word[1] == '\0' || word[1] == '\n'){
					strcpy(word, historyOfCommands[ (commandCount-1) % 10 ]);
				}
				else{
					int pastCommand = word[1] - '0';
					strcpy(word, historyOfCommands[ (commandCount-pastCommand) % 10 ]);
				}
			}

			//History, printing commands from most recent to oldest
			if(strcmp(word, history) == 0){
				int i = count-1;
				int j = 0;
				while((i != count) && (historyOfCommands[i][0] != '\0')){
					if(i < 0){
						i = 9;
					}
					printf("%d %s\n", commandCount-j, historyOfCommands[i]);
					i--;
					j++;
				}
				j++;
				if(historyOfCommands[count][0] != '\0'){
					printf("%d %s\n", commandCount-j, historyOfCommands[count]);
				}
			}

			//Parsing command, turning it into args then executing it. (still needs work for sure.)
			else {
				//seperating into args
				int i = 0;
				int j = 0;
				while(word[i] != '\0'){
					//tokenize args[0]
				}
				pid_t pid = fork();
				//checking last arg to see if it is &
				if(1){
					wait(NULL);
				}
				if(pid == 0){
					execvp(args[0], args)
					//system(word); Works great, but not what we are required to use
				}
				
				//adding line to list of past commands.
				strcpy(historyOfCommands[count], word);
				commandCount++;
			}
		}
	}
	return 0;
}