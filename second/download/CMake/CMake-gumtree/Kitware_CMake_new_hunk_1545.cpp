    fprintf(stderr, "Invalid test number %d.\n", n);

    return 1;

    }

  else if(n >= 1 && n <= 7)

    {

    /* This is the parent process for a requested test number.  */

    int states[7] =

    {

      kwsysProcess_State_Exited,

