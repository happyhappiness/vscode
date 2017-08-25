int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* length,
                          double* userTimeout)
{
  int i;
  int max = -1;
  kwsysProcessTime* timeout = 0;
  kwsysProcessTime timeoutLength;
  kwsysProcessTime timeoutTime;
  kwsysProcessTime userStartTime;
  int user = 0;
  int expired = 0;
  int pipeId = 0;
  int numReady = 0;
  
  /* Record the time at which user timeout period starts.  */
  if(userTimeout)
    {
    userStartTime = kwsysProcessTimeGetCurrent();
    }
  
  /* Calculate the time at which a timeout will expire, and whether it
     is the user or process timeout.  */
  user = kwsysProcessGetTimeoutTime(cp, userTimeout, &timeoutTime);
  
  /* Data can only be available when pipes are open.  If the process
     is not running, cp->PipesLeft will be 0.  */
  while(cp->PipesLeft > 0)
    {
    /* Check for any open pipes with data reported ready by the last
       call to select.  */
    for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
      {
      if(cp->PipeReadEnds[i] >= 0 &&
         FD_ISSET(cp->PipeReadEnds[i], &cp->PipeSet))
        {
        int n;
        
        /* We are handling this pipe now.  Remove it from the set.  */
        FD_CLR(cp->PipeReadEnds[i], &cp->PipeSet);
        
        /* The pipe is ready to read without blocking.  Keep trying to
           read until the operation is not interrupted.  */
        while(((n = read(cp->PipeReadEnds[i], cp->PipeBuffer,
                         KWSYSPE_PIPE_BUFFER_SIZE)) < 0) && (errno == EINTR));
        if(n > 0)
          {
          /* We have data on this pipe.  */
          if(i == KWSYSPE_PIPE_ERROR)
            {
            /* This is data on the special error reporting pipe.  The
               child process failed to execute the program.  */
            cp->ChildError = 1;
            if(n > KWSYSPE_PIPE_BUFFER_SIZE - cp->ErrorMessageLength)
              {
              n = KWSYSPE_PIPE_BUFFER_SIZE - cp->ErrorMessageLength;
              }
            if(n > 0)
              {
              memcpy(cp->ErrorMessage+cp->ErrorMessageLength,
                     cp->PipeBuffer, n);
              cp->ErrorMessageLength += n;
              cp->ErrorMessage[cp->ErrorMessageLength] = 0;
              }
            }
          else if(pipes & (1 << i))
            {
            /* Caller wants this data.  Report it.  */
            *data = cp->PipeBuffer;
            *length = n;
            pipeId = (1 << i);
            break;
            }
          }
        else
          {
          /* We are done reading from this pipe.  */
          kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
          --cp->PipesLeft;
          }
        }
      }
    
    /* If we have data, break early.  */
    if(pipeId)
      {
      break;
      }
    
    /* Make sure the set is empty (it should always be empty here
       anyway).  */
    FD_ZERO(&cp->PipeSet);
    
    /* Add the pipe reading ends that are still open.  */
    max = -1;
    for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
      {
      if(cp->PipeReadEnds[i] >= 0)
        {
        FD_SET(cp->PipeReadEnds[i], &cp->PipeSet);
        if(cp->PipeReadEnds[i] > max)
          {
          max = cp->PipeReadEnds[i];
          }
        }
      }
  
    /* Make sure we have a non-empty set.  */
    if(max < 0)
      {
      /* All pipes have closed.  Child has terminated.  */
      break;
      }
    
    /* Setup a timeout if required.  */
    if(timeoutTime.tv_sec < 0)
      {
      timeout = 0;
      }
    else
      {
      timeout = &timeoutLength;
      }
    if(kwsysProcessGetTimeoutLeft(&timeoutTime, &timeoutLength))
      {
      /* Timeout has already expired.  */
      expired = 1;
      break;
      }
    
    /* Run select to block until data are available.  Repeat call
       until it is not interrupted.  */
    while(((numReady = select(max+1, &cp->PipeSet, 0, 0, timeout)) < 0) &&
          (errno == EINTR));
    
    /* Check result of select.  */
    if(numReady == 0)
      {
      /* Select's timeout expired.  */
      expired = 1;
      break;
      }
    else if(numReady < 0)
      {
      /* Select returned an error.  Leave the error description in the
         pipe buffer.  */
      snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
               "%s", strerror(errno));
      
      /* Kill the child now.  */
      kwsysProcess_Kill(cp);
      cp->Killed = 0;
      cp->ChildError = 1;
      cp->PipesLeft = 0;
      }
    }
  
  /* Update the user timeout.  */
  if(userTimeout)
    {
    kwsysProcessTime userEndTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime difference = kwsysProcessTimeSubtract(userEndTime,
                                                     userStartTime);
    double d = kwsysProcessTimeToDouble(difference);
    *userTimeout -= d;
    if(*userTimeout < 0)
      {
      *userTimeout = 0;
      }
    }
  
  /* Check what happened.  */
  if(pipeId)
    {
    /* Data are ready on a pipe.  */
    return pipeId;
    }
  else if(expired)
    {
    /* A timeout has expired.  */
    if(user)
      {
      /* The user timeout has expired.  It has no time left.  */
      return kwsysProcess_Pipe_Timeout;
      }
    else
      {
      /* The process timeout has expired.  Kill the child now.  */
      kwsysProcess_Kill(cp);
      cp->Killed = 0;
      cp->TimeoutExpired = 1;
      cp->PipesLeft = 0;
      return 0;
      }
    }
  else
    {
    /* No pipes are left open.  */
    return 0;
    }
}