int main(int argc, char **argv)
{
  char *URL;

  memory_tracking_init();

  /*
   * Setup proper locale from environment. This is needed to enable locale-
   * specific behaviour by the C library in order to test for undesired side
   * effects that could cause in libcurl.
   */
#ifdef HAVE_SETLOCALE
  setlocale(LC_ALL, "");
#endif

  if(argc< 2 ) {
    fprintf(stderr, "Pass URL as argument please\n");
    return 1;
  }

  test_argc = argc;
  test_argv = argv;

  if(argc>2)
    libtest_arg2=argv[2];

  if(argc>3)
    libtest_arg3=argv[3];

  URL = argv[1]; /* provide this to the rest */

  fprintf(stderr, "URL: %s\n", URL);

  return test(URL);
}