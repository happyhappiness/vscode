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

