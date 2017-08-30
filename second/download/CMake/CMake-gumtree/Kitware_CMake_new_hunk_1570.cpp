  return 0;

}



int runChild2(kwsysProcess* kp,

              const char* cmd[], int state, int exception, int value,

              int share, int output, int delay, double timeout,

              int poll)

{

  int result = 0;

  char* data = 0;

  int length = 0;

  double userTimeout = 0;

  double* pUserTimeout = 0;

  kwsysProcess_SetCommand(kp, cmd);

  if(timeout >= 0)

    {

