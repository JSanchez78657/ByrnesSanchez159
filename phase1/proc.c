// proc.c, 159
// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

// include spede.h and kernel.h
#include "spede.h"
#include "kernel.h"

#define CORNER 75
#define STRWIDTH 4

// prototype any subroutines of Clock() here
void itos(int, char*);
int str_len(char*);
void display(int, char*);

void Clock() {
   int second = 0;
   int last_tick = 0;
   char str[] = "    ";  // str for 4-digits, plus NUL
   display(second, str);
//   an infinite loop:
   while(1) 
//      if sys_tick is now at a new second
      if(sys_tick != last_tick && sys_tick % CLK_TCK == 0) {
         last_tick = sys_tick;
         display(++second, str);
      }
}

// Program a void-return function:
// given a number and an address of a string, it converts the number
// to the string.
void itos(int i, char* s) {
    //Start at the end of the string, on the character before '\0'
    int h;
    h = str_len(s) - 1;
    //Grab the last number of the integer, put it in the current position of the string, then move it left.
    if(i == 0) s[h] = '0';
    else for(; i > 0; i /= 10) 
        s[h--] = '0' + (i % 10);
}

// Program an integer-return function:
// given a string, the function counts up the length of the string
// and returns it.
int str_len(char* s) {
   int i;
   for(i = 0; s[i] != '\0'; ++i);
   return i;
}

void display(int num, char* str) {
   unsigned short *p;
   unsigned i;
//         convert the current second count number to str
   itos(num, str);
//         set p to VIDEO_START (1st row, 1st column)
   p = (unsigned short *)VIDEO_START;
//         advance p by 75 columns (to the right, on the same row)
   p += CORNER;
//         loop thru each char in str:
//            *p = the character + VIDEO_MASK
   for(i = 0; i < STRWIDTH; ++i)
      *(p + i) = str[i] + VIDEO_MASK;
}
