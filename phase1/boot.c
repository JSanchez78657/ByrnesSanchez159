// boot.c, 159, phase 1
//
// Team Name: ??????? (Members: ??????...)

#include "spede.h"
#include "kernel.h"
#include "entry.h"
#include "misc.h"
#include "proc.h"

// kernel data are all declared here (prototyped in kernel.h):

int cur_pid;
pcb_t pcb[PROC_SIZE];
char stack[PROC_SIZE][STACK_SIZE];
q_t unused_q, ready_q;

unsigned int sys_tick;
struct i386_gate *intr_table;

void CreateProc(func_p_t funEntry)
{
 	int next = DeQ(&unused_q);  
	EnQ(next, &ready_q);

	Bzero(stack[next], STACK_SIZE);	
	pcb[next].run_tick = 0;
	pcb[next].total_tick = 0;
	pcb[next].state = READY;
	
	Bzero((char*) pcb[next].tf_p, sizeof(tf_t));
	
	pcb[next].tf_p->efl = 0;
	pcb[next].tf_p->cs = get_cs();
	pcb[next].tf_p->eip = (unsigned) &funEntry;
}

void main(void) {                   // kernel boots
        int i;
	sys_tick = 0;
	intr_table = (struct i386_gate *) INTR_TABLE;

	Bzero((char *) &unused_q, sizeof(q_t));
	Bzero((char *) &ready_q, sizeof(q_t));

	for (i = 0; i < PROC_SIZE; i++)
	{
		EnQ(i, &unused_q);
	}
	
	fill_gate(&intr_table[TIMER], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);
	
	outportb(PIC_MASK_REG, PIC_MASK);

	
	CreateProc(Clock);

	cur_pid = 0;

	Loader(pcb[0].tf_p); //I'm not sure if this is correct, just a guess.
}
