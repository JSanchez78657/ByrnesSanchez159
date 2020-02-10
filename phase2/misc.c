// misc.c, 159

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

void itos(int i, char*s) {
    int h;
    h = str_len(s) - 1;
    if(i == 0) s[h] = '0';
    else for(; i > 0; i /= 10)
        s[h--] = '0' + (i %10);
}

void StrAdd(char* str, char c) {
    int i;
    for(i = 0; str[i] != '\0'; ++i);
    str[i+1] = '\0';
    str[i] = c;
}
