    }

  

  kwsysProcess_SetCommand(kp, cmd);

  if(timeout >= 0)

    {

    kwsysProcess_SetTimeout(kp, timeout);

    }

  if(share)

    {

    kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDOUT, 1);

    kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDERR, 1);

    }

  kwsysProcess_Execute(kp);



  if(poll)

    {

    pUserTimeout = &userTimeout;

    }



  if(!share)

    {

    int p;

    while((p = kwsysProcess_WaitForData(kp, &data, &length, pUserTimeout)))

      {

      if(output)

        {

        if(poll && p == kwsysProcess_Pipe_Timeout)

          {

          fprintf(stdout, "WaitForData timeout reached.\n");

          fflush(stdout);



          /* Count the number of times we polled without getting data.

             If it is excessive then kill the child and fail.  */

          if(++poll >= MAXPOLL)

            {

            fprintf(stdout, "Poll count reached limit %d.\n",

                    MAXPOLL);

            kwsysProcess_Kill(kp);

            }

          }

        else

          {

          fwrite(data, 1, length, stdout);

          fflush(stdout);

          }

        }

      if(poll)

        {

        /* Delay to avoid busy loop during polling.  */

#if defined(_WIN32)

        Sleep(100);

#else

        usleep(100000);

#endif

        }

      if(delay)

        {

