static void kwsys_shared_forward_print_failure(char const* const* argv)
{
  char msg[KWSYS_SHARED_FORWARD_MAXPATH];
  char const* const* arg = argv;
  kwsys_shared_forward_strerror(msg);
  fprintf(stderr, "Error running");
  for (; *arg; ++arg) {
    fprintf(stderr, " \"%s\"", *arg);
  }
  fprintf(stderr, ": %s\n", msg);
}