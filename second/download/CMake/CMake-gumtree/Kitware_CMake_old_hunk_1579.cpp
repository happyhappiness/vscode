    }
}


int runChild(const char* cmd[], int state, int exception, int value,
             int share, int output, int delay, double timeout)
{
  int result = 0;
  char* data = 0;
  int length = 0;
  kwsysProcess* kp = kwsysProcess_New();
  if(!kp)
    {
