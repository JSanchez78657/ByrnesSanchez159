// proc.c, 159

/*
need to include "syscall.h" to call the new OS services

program a void-returning Init that has no input
   loop forever:
      call get_time_call() to get current time in seconds
      convert time to a smaller time str
      call write_call to show time_str
      ...
      ... see demo run to issue calls to perform the same...
      ...
   }
}

*/

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

// include spede.h and kernel.h

#include "spede.h"
#include "kernel.h"
#include "misc.h"
#include "syscall.h"

#define CORNER 75
#define STRWIDTH 4

void itos(int, char*);
int str_len(char*);
void display(int, char*);

void Clock() {
   int second = 0;
   int last_tick = 0;
   char str[] = "    ";  
   display(second, str);
   while(1) 
      if(sys_tick != last_tick && sys_tick % CLK_TCK == 0) {
         last_tick = sys_tick;
         display(++second, str);
      }
}

void display(int num, char* str) {
   unsigned short *p;
   unsigned i;
   itos(num, str);
   p = (unsigned short *)VIDEO_START;
   p += CORNER;
   for(i = 0; i < STRWIDTH; ++i)
      *(p + i) = str[i] + VIDEO_MASK;
}

void Init() {
    int seconds;
    char* str;
    while(1) {
        seconds = get_time_call();
        itos(str, seconds);
}
