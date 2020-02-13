/*
// misc.c, 159

add 2 new functions:

// assume: str is NUL-delimited, and has >0 byte space left
void-returning StrAdd with 2 input: a character and a char * (string)
   we want to append the new character at the end of the string
   so we first need to find the end of the string by advancing
   the string pointer until it point to a NUL, and that's where
   the new character is added, and next to the new character is
   a new NUL to keep the string NUL-delimited.

// assume: source string is properly NUL-delimited, destination is
// large enough in space to perform the copying
void-returning StrCpy with 2 inputs: both char *, as the source
and destination of the copy
make sure the destination copy will also be NUL-delimited
=======

*/
#include "spede.h"
#include "kernel.h"

int QisEmpty(q_t *myQ)
{
	return (myQ->size == 0) ? TRUE : FALSE;
}

int QisFull(q_t *myQ)
{
	return (myQ->size == 20) ? TRUE : FALSE;
}

int DeQ(q_t *myQ)
{
	if (!QisEmpty(myQ))
	{
		int temp = myQ->q[myQ->head];
		++myQ->head;
		--myQ->size;
		return temp;
	}
	else
	{
		return 0;
	}
}


void EnQ(int pid, q_t *myQ)
{
	if (!QisFull(myQ))
	{
		++myQ->size;
		myQ->q[(myQ->tail++) % Q_SIZE] = pid;
	}

	else
	{
		cons_printf("Panic: queue is full, cannot EnQ!\n");
		breakpoint();
	}
}

void Bzero(char *myChar, unsigned nBytes)
{
        int i;
	for (i = 0; i < nBytes; i++)
	{
		myChar[i] =0;
	}
}


void MemCpy(char *source, char *dest, unsigned nBytes)
{
        int i;
	for (i = 0; i < nBytes; i++)
	{
		dest[i] = source[i];
	}
}

int str_len(char* s) {
    int i;
    for(i = 0; s[i] != '\0'; ++i);
    return i;
}

void itos(int i, char* s) {
    int h;
    h = str_len(s) - 1;
    if(i == 0) s[h] = '0';
    else for(; i > 0; i /= 10)
        s[h--] = '0' + (i %10);
}

void StrAdd(char* str, char c) {
    int len = str_len(str);
    str[len+1] = '\0';
    str[len] = c;
}

void StrCpy(char* inStr, char* destStr) {
    int len = str_len(inStr);
    int i;
    for(i = 0; i < len; ++i)
        destStr[i] = inStr[i];
}
