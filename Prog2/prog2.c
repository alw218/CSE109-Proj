 /*
  CSE 109
  Amber Wallace
  alw218
  Program Description:
  Program #2
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char ** getopts(char cmd[]);

int main(int argc, char *argv[]){
  char *scommand = "start";
 
  char host[200];
  gethostname(host,200);

  const char *ecommand = "exit";
  int strcmpr;
  while((strcmpr = strcmp(scommand,ecommand)) != 0){
    printf("%s>",host);
    char command[200];
    fgets(command,200,stdin);

    const char s[3] = "\n";

    scommand = strtok(command,s);
    
    /*if user didn't type exit*/
    if(strcmp(scommand,ecommand) != 0){
      char **argv = getopts(scommand);
      if(fork() == 0){
	execvp(argv[0], argv);
      } else {
	wait(NULL);
      }
     
    }
      
  }

  return(0);
  
}
