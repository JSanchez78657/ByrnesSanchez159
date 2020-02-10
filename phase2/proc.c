#include "spede.h"
#include "kernel.h"
#include "misc.h"

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
