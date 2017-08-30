  fprintf(stderr, "Output on stderr before grandchild test.\n");

  fflush(stdout);

  fflush(stderr);

  r = runChild(cmd, kwsysProcess_State_Exited, kwsysProcess_Exception_None, 0,

               1, 1, 0, 30, 0, 1, 0, 0, 0);

  /* This sleep will avoid a race condition between this function exiting

     normally and our Ctrl+C handler exiting abnormally after the process

     exits.  */

