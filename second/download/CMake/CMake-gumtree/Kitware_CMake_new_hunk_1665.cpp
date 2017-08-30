  return 0;

}



int test4(int argc, const char* argv[])

{

  (void)argc; (void)argv;

  fprintf(stdout, "Output before crash on stdout from crash test.\n");

  fprintf(stderr, "Output before crash on stderr from crash test.\n");  

  fflush(stdout);

