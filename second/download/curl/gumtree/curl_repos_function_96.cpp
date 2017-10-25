static int rlimit(void)
{
  int i;
  struct rlimit rl;

  fprintf(stderr, "NUM_OPEN: %d\n", NUM_OPEN);
  fprintf(stderr, "NUM_NEEDED: %d\n", NUM_NEEDED);

  /* get open file limits */
  if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
    fprintf(stderr, "warning: getrlimit: failed to get RLIMIT_NOFILE\n");
    return -1;
  }

  /* check that hard limit is high enough */
  if (rl.rlim_max < NUM_NEEDED) {
    fprintf(stderr, "warning: RLIMIT_NOFILE hard limit %d < %d\n",
            (int)rl.rlim_max, NUM_NEEDED);
    return -2;
  }

  /* increase soft limit if needed */
  if (rl.rlim_cur < NUM_NEEDED) {
    rl.rlim_cur = NUM_NEEDED;
    if (setrlimit(RLIMIT_NOFILE, &rl) == -1) {
      fprintf(stderr, "warning: setrlimit: failed to set RLIMIT_NOFILE\n");
      return -3;
    }
  }

  /* open a dummy descriptor */
  fd[0] = open(DEV_NULL, O_RDONLY);
  if (fd[0] == -1) {
    fprintf(stderr, "open: failed to open %s\n", DEV_NULL);
    return -4;
  }

  /* create a bunch of file descriptors */
  for (i = 1; i < NUM_OPEN; i++) {
    fd[i] = dup(fd[0]);
    if (fd[i] == -1) {
      fprintf(stderr, "dup: attempt #%i failed\n", i);
      for (i--; i >= 0; i--)
        close(fd[i]);
      return -5;
    }
  }

  return 0;
}