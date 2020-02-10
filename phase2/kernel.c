// kernel.c

...

void-returning TimerService has an argument: tf_t *tf_p {
   ... 1st save tf_p ...
   if the keyboard on the PC is pressed {
      get the key
      if it's 'g,' goto GDB
      if keyboard wait queue is not empty: call KbService with the key as argument
   }
   ... rest unchanged ...
}

...

void-returning GetTimeService with an argument: tf_t *tf_p {
   copy current second # to 'eax' in the TF that tf_p points to
   call Loader with tf_p as the argument to (resume the same process)
}

void-returning WriteService with an input argument: tf_t *tf_p {
   the address of the str to print is given in 'eax' of the TF
   that tf_p points to

   for each char in the string (that's not NUL) {
      call WriteChar with that char as the argument
      advance the string pointer
   }

   call Loader with tf_p as the argument to (resume the same process)
}

void-returning WriteChar that's given a char as its argument: {
   declare: static unsigned short *cursor with value = (typecast) VIDEO_START

   if ch is neither CR or NL {   // if it's a regular character
      apply pointer 'cursor' to display the character passed over
      advance 'cursor'
   } else {         // the character to display is a CR or NL
      judging from 'cursor,' calculate how many columns are left in current row
      then in a loop, show that many spaces (to mimic erasing to end of line)
   }

   if 'cursor' reaches bottom-right on screen, set it back to top-left
}

void-returning ReadService with an argument: tf_t *tf_p {
   save tf_p to the PCB of the currently-running process

   move current PID to the wait queue of the keyboard
   alter its state to WAIT
   current PID becomes NA

   call Swapper to find another process to run
   call Loader to load the TF of the newly selected current PID to run it
}

// lower half of ReadService, called by TimerService()
void-returning KbService with a given character as argument {
   call WriteChar with the character to echo/display it

   if the character is not CR {          // DOS uses CR
      call StrAdd to add it to the keyboard buffer  // save it
   } else {
      call StrAdd to add a NUL to the keyboard buffer
      realease the process by dequeuing PID from the keyboard wait queue
      the string space is pointed to by 'eax' of the process TF
      call StrCpy to copy the keyboard.buffer to the process string space
      alter the released process state to READY
      move it to the ready queue
      clear/empty the keyboard buffer
   }
}

