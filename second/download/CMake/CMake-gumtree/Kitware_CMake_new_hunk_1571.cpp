            poll, MINPOLL);

    result = 1;

    }



  return result;

}



int runChild(const char* cmd[], int state, int exception, int value,

             int share, int output, int delay, double timeout,

             int poll, int repeat)

{

  int result;

  kwsysProcess* kp = kwsysProcess_New();

  if(!kp)

    {

    fprintf(stderr, "kwsysProcess_New returned NULL!\n");

    return 1;

    }

  while(repeat-- > 0)

    {

    result = runChild2(kp, cmd, state, exception, value, share,

                       output, delay, timeout, poll);

    }

  kwsysProcess_Delete(kp);

  return result;

}

