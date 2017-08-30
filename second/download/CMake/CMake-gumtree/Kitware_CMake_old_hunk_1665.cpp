  return 0;
}

int test4()
{
  fprintf(stdout, "Output before crash on stdout from crash test.\n");
  fprintf(stderr, "Output before crash on stderr from crash test.\n");  
  fflush(stdout);
