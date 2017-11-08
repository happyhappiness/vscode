void usage(char *progname) {
  printf("\nZeusBench v1.0\n\n");
  printf("Usage: %s <machine> <file> [-k] [-n requests | -t timelimit (sec)]"
         "\n\t\t[-c concurrency] [-p port] \n",progname);
  printf("Filename should start with a '/' e.g. /index.html\n\n");
  exit(EINVAL);
}