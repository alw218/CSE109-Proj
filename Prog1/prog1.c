/*
  CSE 109
  Amber Wallace
  alw218
  Program Description:
  Program #1
*/

/*
Create a main function and any additional functions necessary to do the following:
  1. Create a filter program that reads from standard input and writes to standard output.
    2. The program should read the input text line for line, and, if there are no command line options, then
    write each line as is to standard output.
    3. Do the following for each of the following command line options:
    1. -u – convert all the text to upper case.
      2. -r – reverse each word in the text (a word is a string of chars surrounded by blanks).
      3. If both options are given then both changes should be made.
      4. Any other option should cause an “Invalid command line option” message along with the option
      itself to be displayed to standard error before quitting the program.
*/
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
  int uflag = 0;
  int rflag = 0;
  int c;
  int ch;
  while((c = getopt(argc, argv, "ur")) != -1){
    switch(c){
    case 'u':
      uflag = 1;
      break;
    case 'r':
      rflag = 1;
      break;
    case '?':
      return 1;
    default:
      abort ();
    }
  }
  if(rflag){
    reverse(uflag);
  }
  else{
     while((ch = getchar())!= EOF){
      if(uflag)
	ch = toupper(ch);
      putchar(ch);
    }
  }
  return(0);
}

void reverse(int uflag){
  int ch;
  int count = 0;
  int  word[100];
  while((ch = getchar())!= EOF){
    if(ch == ' '){
      reverseword(word,count);
      count = 0;
    }
    else{
      if(uflag)
	word[count] = toupper(ch);
      else
	word[count] = ch;
      count++;
    }
  }
}

void reverseword(int word[],int count){
  while(count > 0){
    count--;
    putchar(word[count]);
  }
  putchar(' ');
}
    
