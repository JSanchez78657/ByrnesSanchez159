// proc.c, 159
// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

// include spede.h and kernel.h
#include <spede.h>
#include <kernel.h>

#define CORNER 75
#define STRWIDTH 4

// prototype any subroutines of Clock() here
void itos(int, char*);
int strlen(char*);

void Clock() {
   int tick = 0;
   int i;
   char str[] = "    ";  // str for 4-digits, plus NUL
   unsigned short *p;

//   an infinite loop:
   while(1) {
//      if sys_tick is now at a new second
      if(sys_tick % CLK_TICK == 0) {
         ++tick;
//         convert the current second count number to str
         str = itos(tick);
//         set p to VIDEO_START (1st row, 1st column)
         p = VIDEO_START;
//         advance p by 75 columns (to the right, on the same row)
         p += CORNER;
//         loop thru each char in str:
//            *p = the character + VIDEO_MASK
         for(i = 0; i < STRWIDTH; ++i)
            *p = str[i] + VIDEO_MASK;
}

// Program a void-return function:
// given a number and an address of a string, it converts the number
// to the string.
void itos(int i, char* s) {
    //Start at the end of the string, on the character before '\0'
    int h = strlen(s) - 1;
    //Grab the last number of the integer, put it in the current position of the string, then move it left.
    for(; i > 0; i /= 10)
        s[h--] = '0' + (i % 10);
}

// Program an integer-return function:
// given a string, the function counts up the length of the string
// and returns it.
int strlen(char* s) {
   int i;
   for(i = 0; s[i] != '\0'; ++i);
   return i;
}
