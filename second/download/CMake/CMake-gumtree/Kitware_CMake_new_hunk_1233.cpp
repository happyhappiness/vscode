  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Exception,
               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 3);
  fprintf(stdout, "Output on stdout after recursive test.\n");
  fprintf(stderr, "Output on stderr after recursive test.\n");
  fflush(stdout);
