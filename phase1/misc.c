// misc.c, 159

#include "spede.h"
#include "kernel.h"

int QisEmpty(q_t *myQ)
{
	return (myQ->size == 0) ? 1 : 0;
}

int QisFull(q_t *myQ)
{
	return (myQ->size == 20) ? 1 : 0;
}

int DeQ(q_t *myQ)
{
	if (!QisEmpty(myQ))
	{
		int temp = myQ->q[myQ->head];
		++myQ->head;
		--myQ->size;
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
		myQ->q[myQ->tail++] = pid;
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
		myChar[i] = NULL;
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
