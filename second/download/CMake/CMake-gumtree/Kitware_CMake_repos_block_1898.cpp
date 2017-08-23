{
  /* Test Ctrl+C behavior: the root test program will send a Ctrl+C to this
     process.  Here, we start a child process that sleeps for a long time
     while ignoring signals.  The test is successful if this process waits
     for the child to return before exiting from the Ctrl+C handler.

     WARNING:  This test will falsely pass if the share parameter of runChild
     was set to 0 when invoking the test9 process.  */
  int r;
  const char* cmd[4];
  (void)argc;
  cmd[0] = argv[0];
  cmd[1] = "run";
  cmd[2] = "109";
  cmd[3] = 0;
  fprintf(stdout, "Output on stdout before grandchild test.\n");
  fprintf(stderr, "Output on stderr before grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Exited, kwsysProcess_Exception_None, 0,
               1, 1, 0, 30, 0, 1, 0, 0, 0);
  /* This sleep will avoid a race condition between this function exiting
     normally and our Ctrl+C handler exiting abnormally after the process
     exits.  */
  testProcess_sleep(1);
  fprintf(stdout, "Output on stdout after grandchild test.\n");
  fprintf(stderr, "Output on stderr after grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  return r;
}