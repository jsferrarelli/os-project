#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

// This file contains all command implementation

// declaring the functions to be implemented
int shell_exit();
int shell_help();
int shell_cd(char **args);
int shell_pwd();
int shell_mkdir(char **args);
int shell_rmdir(char **args);
int shell_chmod();
int shell_cp();


// list of available commands
char *commandString[] = {"exit", "help", "cd", "pwd", "mkdir", "rmdir", "chmod", "cp"};

int (*commandFunction[]) (char **) = { &shell_exit, &shell_help, &shell_cd, &shell_pwd, &shell_mkdir, &shell_rmdir, &shell_chmod, &shell_cp };

// returns length of commands[]
int commandSize() {
	return sizeof(commandString) / sizeof(char*);
}

// change all the return types and parameters passed as see fit
int shell_cd(char **args) {
		char* t = *args;
        chdir(t);
        return 1;
}

int shell_pwd() {
        char cwd[1024];
        printf("%s\n",getcwd(cwd, sizeof(cwd)));
        return 1;
}

int shell_mkdir(char **args) {
		char *dir = *args;
        mkdir(dir, 00777);
        printf("made new directory %s\n",dir);
        return 1;
}

int shell_rmdir(char **args) {
		char* dir = *args;
        rmdir(dir);
        printf("removed directory %s\n",dir);
        return 1;
}

int shell_chmod(char **arg1, char **arg2) {
		char* permissions = *arg1;
		char* path = *arg2;
        chmod(path, strtol(permissions,0,8));
        return 1;
}

const int N = 80;
int shell_cp(char **arg1, char **arg2) {
		char* loc1 = *arg1;
		char* loc2 = *arg2;
        int f1,f2; 
        char buff [N];
        long int n;
        if((f1 = open(loc1, O_RDONLY)) == -1)
        {
         perror("Input file failed to open \n");
         exit(EXIT_FAILURE);
        }

        if((f2  = open(loc2, O_WRONLY | O_CREAT | O_TRUNC, 0744))==-1) {
                perror("Output failure \n");
                exit(EXIT_FAILURE);
        }

        while((n=read(f1,buff, N))>0) { //0 indicates EOF
                if(write(f2, buff, n) != n) {
                        perror("Error writing to stdout.\n");
                }
}
        close(f1);
        close(f2);

        return 1;
}


// below are a couple of functions for more accessibility 

int shell_exit() {
	return 0;
}

int shell_help() {
	puts("NautonShell implementation by James Ferrarelli and Shane Lopez, OS Fall 2019");
	puts("Enter valid command names, followed by any arguments they require");
	puts("Here are our available commands: ");
	for(int i = 0; i < commandSize(); i++) {
		printf("	%s\n", commandString[i]);
	}
	return 1;	
}

