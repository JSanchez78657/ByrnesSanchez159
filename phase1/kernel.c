// kernel.c, 159, phase 1
//
// Team Name: ??????? (Members: ??????...)

#include "spede.h"
#include "kernel.h"
#include "proc.h"
#include "misc.h"
#include "entry.h"

void TimerService(tf_t *trapframe)
{
	char ch;
	outportb(PIC_CONTROL_REG, TIMER_ACK);

	trapframe = pcb[cur_pid].tf_p;
	
	if (cons_kbhit())
	{
		ch = cons_getchar();
		if (ch == 'g') breakpoint();
	}	
	
	++sys_tick;
	++pcb[cur_pid].run_tick;
	++pcb[cur_pid].total_tick;

	if (pcb[cur_pid].run_tick == TIME_SIZE)
	{
		EnQ(cur_pid, &ready_q);
		pcb[cur_pid].state = READY;
		cur_pid = -1;
	}		

	if (cur_pid == -1)
	{
		Swapper();
	}

}

void Swapper()
{
	if (QisEmpty(&ready_q))
	{
		cons_printf("Kernel: panic, no more processes ready to run!\n");		breakpoint();
	}

	else
	{
		cur_pid = DeQ(&ready_q);
		pcb[cur_pid].run_tick = 0;
		pcb[cur_pid].state = RUN;
	}				
}

