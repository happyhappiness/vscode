int main(int argc, const char* argv[])
{
  int n = 0;
  if(argc == 2)
    {
    n = atoi(argv[1]);
    }
  else if(argc == 3)
    {
    n = atoi(argv[2]);
    }
  /* Check arguments.  */
  if(n < 1 || n > 5 || (argc == 3 && strcmp(argv[1], "run") != 0))
    {
    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
    return 1;
    }
  if(argc == 3)
    {
    switch (n)
      {
      case 1: return test1();
      case 2: return test2();
      case 3: return test3();
      case 4: return test4();
      }
    fprintf(stderr, "Invalid test number %d.\n", n);
    return 1;
    }
  
  if(n <= 4)
    {
    int states[4] =
      {
        kwsysProcess_State_Exited,
        kwsysProcess_State_Exited,
        kwsysProcess_State_Expired,
        kwsysProcess_State_Exception
      };
    int exceptions[4] = {kwsysProcess_Exception_None, kwsysProcess_Exception_None,
                         kwsysProcess_Exception_None, kwsysProcess_Exception_Fault};
    int values[4] = {0, 123, 1, 1};
    const char* cmd[4];
    cmd[0] = argv[0];
    cmd[1] = "run";
    cmd[2] = argv[1];
    cmd[3] = 0;
    return runChild(cmd, states[n-1], exceptions[n-1], values[n-1]);
    }
  else
    {
    return 0;
    }  
}