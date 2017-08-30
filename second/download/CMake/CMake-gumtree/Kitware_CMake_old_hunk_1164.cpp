   delaying 1/10th of a second should ever have to poll.  */
#define MINPOLL 5
#define MAXPOLL 20
int test7(int argc, const char* argv[])
{
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout before sleep.\n");
