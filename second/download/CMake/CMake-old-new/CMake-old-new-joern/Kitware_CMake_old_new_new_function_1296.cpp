int runChild(const char* cmd[], int state, int exception, int value,
             int share, int output, int delay, double timeout)
{
  int result = 0;
  char* data = 0;
  int length = 0;
  kwsysProcess* kp = kwsysProcess_New();
  if(!kp)
    {
    fprintf(stderr, "kwsysProcess_New returned NULL!\n");
    return 1;
    }
  
  kwsysProcess_SetCommand(kp, cmd);
  kwsysProcess_SetTimeout(kp, timeout);
  if(share)
    {
    kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDOUT, 1);
    kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDERR, 1);
    }
  kwsysProcess_Execute(kp);

  if(!share)
    {
    while(kwsysProcess_WaitForData(kp, &data, &length, 0))
      {
      if(output)
        {
        fwrite(data, 1, length, stdout);
        fflush(stdout);
        }
      if(delay)
        {
        /* Purposely sleeping only on Win32 to let pipe fill up.  */
#if defined(_WIN32)
        Sleep(100);
#endif
        }
      }
    }
  
  kwsysProcess_WaitForExit(kp, 0);
  
  switch (kwsysProcess_GetState(kp))
    {
    case kwsysProcess_State_Starting:
      printf("No process has been executed.\n"); break;
    case kwsysProcess_State_Executing:
      printf("The process is still executing.\n"); break;
    case kwsysProcess_State_Expired:
      printf("Child was killed when timeout expired.\n"); break;
    case kwsysProcess_State_Exited:
      printf("Child exited with value = %d\n",
             kwsysProcess_GetExitValue(kp));
      result = ((exception != kwsysProcess_GetExitException(kp)) ||
                (value != kwsysProcess_GetExitValue(kp))); break;
    case kwsysProcess_State_Killed:
      printf("Child was killed by parent.\n"); break;
    case kwsysProcess_State_Exception:
      printf("Child terminated abnormally: %s\n",
             kwsysProcess_GetExceptionString(kp));
      result = ((exception != kwsysProcess_GetExitException(kp)) ||
                (value != kwsysProcess_GetExitValue(kp))); break;
    case kwsysProcess_State_Error:
      printf("Error in administrating child process: [%s]\n",
             kwsysProcess_GetErrorString(kp)); break;
    };
  
  if(result)
    {
    if(exception != kwsysProcess_GetExitException(kp))
      {
      fprintf(stderr, "Mismatch in exit exception.  "
              "Should have been %d, was %d.\n",
              exception, kwsysProcess_GetExitException(kp));
      }
    if(value != kwsysProcess_GetExitValue(kp))
      {
      fprintf(stderr, "Mismatch in exit value.  "
              "Should have been %d, was %d.\n",
              value, kwsysProcess_GetExitValue(kp));
      }
    }
  
  if(kwsysProcess_GetState(kp) != state)
    {
    fprintf(stderr, "Mismatch in state.  "
            "Should have been %d, was %d.\n",
            state, kwsysProcess_GetState(kp));
    result = 1;
    }
  
  kwsysProcess_Delete(kp);
  return result;
}