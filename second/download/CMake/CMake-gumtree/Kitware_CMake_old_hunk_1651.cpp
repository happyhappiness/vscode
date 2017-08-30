  fflush(stdout);

  fflush(stderr);

  r = runChild(cmd, kwsysProcess_State_Exception,

               kwsysProcess_Exception_Fault, 1, 1, 2);

  fprintf(stdout, "Output on stdout after recursive test.\n");

  fprintf(stderr, "Output on stderr after recursive test.\n");

  fflush(stdout);

  fflush(stderr);

  return r;

}





int runChild(const char* cmd[], int state, int exception, int value,

             int share, double timeout)

{

  int result = 0;

  char* data = 0;

