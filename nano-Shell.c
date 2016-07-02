/*
Mini-Shell
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/wait.h>
#include <sys/types.h>

//Global variable;
char *args[100]; // math pointer
char first[20]; // vect for command;
extern char ** environ;
char **env;
// function declarations ;

int  numbers_arg( char * , int );
void matrix_numbers_arg( char *);
void run( char ** );
void clear_math();
void shell_std();

//Start
int main(){
  char line[512]; // user input
  char line_cpy[512];
  int  i , index_arg=0;
  char *st;
  clear_math();
  printf("Welcome to Mini-Shell\n  Type \'exit\' to EXIT!!\n");
  while (strcmp(first,"exit")!=0){
    index_arg=0;  // command's numbers;
    shell_std();  // prompt -$_Unix_Shell_$
    if(!fgets(line,512,stdin))
      return 0;
    line[strlen(line)-1]='\n';
    st=line;
    strcpy(line_cpy,line);

    if (strcmp(line,"printenv\n")==0){
      for (env = environ; *env != NULL; ++env)
        printf ("%s\n", *env);
      clear_math();
    }
    else if (strcmp(line,"exit\n")==0){
      clear_math();
      strcpy(first,"exit");
    }
    else if( (strcmp(line,"\n")==0) || (strncmp(line, " ", 1)==0) ){
      clear_math();
    }
    else{
      index_arg=numbers_arg(line_cpy,index_arg);
      matrix_numbers_arg(st);
      run(args);
      clear_math();
    }
  }
  return 0;
}

// Defining FUNCTIONS

/*

Split single string separated (" ") ;
add this string in a math (args[]);
*/
void matrix_numbers_arg( char *p)
{
  int i=0;
  p=strtok(p," \n");
  while(p !=NULL){
    args[i]=p;
    p=strtok(NULL," \n");
    i += 1;
  }
}
/*
count elements in string;
*/
int numbers_arg(char *p , int n)
{
  p=strtok(p," \n");
  strcpy(first,p);
  while(p !=NULL){
    n++;
    p=strtok(NULL," \n");
  }
  return n;
}
/*
  run the program;
*/
void run(char **h ){
  pid_t pid;
  int status;
  pid = fork();
  if (pid == 0){
    if (execvp( first, args) == -1){
      printf("command not found\n");
      exit(EXIT_FAILURE);
    }
    exit(0);
  }
  else{
    wait(&status);
    if(status == 0)
      printf("!SUCCESS!\n");
  }
}
/*
initialization NULL all pointers;
*/
void clear_math(){
  int k=0;
  for(k=0;k<100;k++)
    args[k]=NULL;
}
/*
print a shell output;
*/
void shell_std(){
  printf("[$_Unix_Shell_$ ");
}
