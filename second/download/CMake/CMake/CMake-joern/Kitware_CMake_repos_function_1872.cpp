static int test1(int argc, const char* argv[])
{
  /* This is a very basic functional test of kwsysProcess.  It is repeated
     numerous times to verify that there are no resource leaks in kwsysProcess
     that eventually lead to an error.  Many versions of OS X will fail after
     256 leaked file handles, so 257 iterations seems to be a good test.  On
     the other hand, too many iterations will cause the test to time out -
     especially if the test is instrumented with e.g. valgrind.

     If you have problems with this test timing out on your system, or want to
     run more than 257 iterations, you can change the number of iterations by
     setting the KWSYS_TEST_PROCESS_1_COUNT environment variable.  */
  (void)argc;
  (void)argv;
  fprintf(stdout, "Output on stdout from test returning 0.\n");
  fprintf(stderr, "Output on stderr from test returning 0.\n");
  return 0;
}