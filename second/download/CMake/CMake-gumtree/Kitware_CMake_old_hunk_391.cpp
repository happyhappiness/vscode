  fprintf(stderr, "Output on stderr before grandchild test.\n");

  fflush(stdout);

  fflush(stderr);

  r = runChild(cmd, kwsysProcess_State_Exception,

               kwsysProcess_Exception_Interrupt,

               0, 1, 1, 0, 30, 0, 1, 0, 1, 0);

  fprintf(stdout, "Output on stdout after grandchild test.\n");

  fprintf(stderr, "Output on stderr after grandchild test.\n");

  fflush(stdout);

