  fprintf(stderr, "Output on stderr before recursive test.\n");

  fflush(stdout);

  fflush(stderr);

  r = runChild(cmd, kwsysProcess_State_Exception,

               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1, 0, 0, 0);

  fprintf(stdout, "Output on stdout after recursive test.\n");

  fprintf(stderr, "Output on stderr after recursive test.\n");

  fflush(stdout);

  fflush(stderr);

  return r;

}



#define TEST6_SIZE (4096*2)

static void test6(int argc, const char* argv[])

{

  int i;

  char runaway[TEST6_SIZE+1];

  (void)argc; (void)argv;

  for(i=0;i < TEST6_SIZE;++i)

    {

    runaway[i] = '.';

    }

  runaway[TEST6_SIZE] = '\n';



  /* Generate huge amounts of output to test killing.  */

  for(;;)

    {

    fwrite(runaway, 1, TEST6_SIZE+1, stdout);

    fflush(stdout);

    }

}



/* Define MINPOLL to be one more than the number of times output is

