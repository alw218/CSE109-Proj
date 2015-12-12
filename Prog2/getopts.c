/*
CSE 109
Amber Wallace
alw218
Program Description:
Program #2
*/

#include <string.h>
#include <stdlib.h>

char ** getopts(char cmd[]){
  char newstring[500];
  strcpy(newstring, cmd);
  const char s[2] = " ";
  int stringcount = 0;
  char *token = strtok(newstring,s);
  while(token != NULL){
    stringcount++;
    token = strtok(NULL,s);
  }
  char **argv = malloc(stringcount * sizeof(char *));
  char newstring2[500];
  strcpy(newstring2, cmd);
  token = strtok(newstring2,s);
  int i = 0;
  while(token != NULL){
    argv[i] = malloc(strlen(token)*sizeof(char));
    strcpy(argv[i],token);
    i++;
    token = strtok(NULL,s);
  }
  return(argv);
}
