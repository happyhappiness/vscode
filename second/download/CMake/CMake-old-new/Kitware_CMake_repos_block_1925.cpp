{
      fprintf(stderr, "Mismatch in exit value.  "
                      "Should have been %d, was %d.\n",
              value, kwsysProcess_GetExitValue(kp));
    }