  fflush(stdout);

  fflush(stderr);

  r = runChild(cmd, kwsysProcess_State_Disowned, kwsysProcess_Exception_None,

               1, 1, 1, 0, 10, 0, 1, 1);

  fprintf(stdout, "Output on stdout after grandchild test.\n");

  fprintf(stderr, "Output on stderr after grandchild test.\n");

  fflush(stdout);

