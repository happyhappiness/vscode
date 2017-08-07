{
      fprintf(stderr, "Mismatch in exit exception.  "
                      "Should have been %d, was %d.\n",
              exception, kwsysProcess_GetExitException(kp));
    }