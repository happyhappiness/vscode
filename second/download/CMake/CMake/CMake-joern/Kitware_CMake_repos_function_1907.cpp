static int test10(int argc, const char* argv[])
{
  /* Test Ctrl+C behavior: the root test program will send a Ctrl+C to this
     process.  Here, we start a child process that sleeps for a long time and
     processes signals normally.  However, this grandchild is created in a new
     process group - ensuring that Ctrl+C we receive is sent to our process
     groups.  We make sure it exits anyway.  */
  int r;
  const char* cmd[4];
  (void)argc;
  cmd[0] = argv[0];
  cmd[1] = "run";
  cmd[2] = "110";
  cmd[3] = 0;
  fprintf(stdout, "Output on stdout before grandchild test.\n");
  fprintf(stderr, "Output on stderr before grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  r =
    runChild(cmd, kwsysProcess_State_Exception,
             kwsysProcess_Exception_Interrupt, 0, 1, 1, 0, 30, 0, 1, 0, 1, 0);
  fprintf(stdout, "Output on stdout after grandchild test.\n");
  fprintf(stderr, "Output on stderr after grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  return r;
}