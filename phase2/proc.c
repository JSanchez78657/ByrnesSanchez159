// proc.c, 159
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

