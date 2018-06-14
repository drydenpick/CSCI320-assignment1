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
	char word[50];
	char historyOfCommands[10][50];
	int commandCount = 0;
	int count = 0;

	while (should_run) {
		if(strcmp(word, quit) == 0){
			should_run = 0;
		}
		printf("CSCI3120>");
		fflush(stdout);
		fgets(word, 50, stdin);
		count = commandCount % 10;
		if (word[0] != '\0') {

			// TODO: History commands that will access past commands and past commands will replace Word. Word to be tokenized later.
			if (word[0] == '!') {
				if(word[1] == '!'){
					strcpy(word, historyOfCommands[ (commandCount-1) % 10 ]);
				}
				else{
					int pastCommand = word[1] - '0';
					if(pastCommand < commandCount){
						strcpy(word, historyOfCommands[ (commandCount-pastCommand) % 10 ]);
					}
					else{
						printf("That many commands have not been entered yet\n");
					}
				}
			}

			//History, printing commands from most recent to oldest

			if(strcmp(word, history) == 0){
				if(commandCount == 0){
					printf("No Commands in History");
				}
				else{
					int i = count-1;
					int j = 0;
					if(i < 0){
						i = 9;
					}
					while((i != count) && (historyOfCommands[i][0] != '\0')){
						printf("%d %s", commandCount-j, historyOfCommands[i]);
						i--;
						j++;
						if(i < 0){
							i = 9;
						}
					}
					if(commandCount > 9){
						printf("%d %s", commandCount-j, historyOfCommands[count]);
					}
				}
			}

			//Parsing command, turning it into args then executing it. (still needs work for sure.)
			else {
				//Storing command before parsing it.
				strcpy(historyOfCommands[count], word);
				commandCount++;

				//tokenizing into args
				int y = 0;
				char delimit[]=" \t\r\n\v\f"; 
				char *token = strtok(word, delimit);
				while(token != NULL){
				    char *temp = token;
				    args[y] = temp;
				    y++;
				    
				    token = strtok(NULL, delimit);
				    
				}

				args[y]=NULL;
				//checking last arg to see if it is &
				int shouldWait=1;
				if(*args[y-1]=='&'){
					shouldWait=0;
					args[y-1]=NULL;
				}

				pid_t pid = fork();
				if(shouldWait){
					wait(NULL);
				}
				if(pid == 0){
					execvp(args[0], args);
				}
			}
		}
	}
	return 0;
}