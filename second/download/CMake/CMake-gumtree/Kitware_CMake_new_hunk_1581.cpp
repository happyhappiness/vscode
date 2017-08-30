            state, kwsysProcess_GetState(kp));
    result = 1;
    }

  /* We should have polled more times than there were data if polling
     was enabled.  */
  if(poll && poll < MINPOLL)
    {
    fprintf(stderr, "Poll count is %d, which is less than %d.\n",
            poll, MINPOLL);
    result = 1;
    }
  
  kwsysProcess_Delete(kp);
  return result;
