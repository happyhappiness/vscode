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

  

