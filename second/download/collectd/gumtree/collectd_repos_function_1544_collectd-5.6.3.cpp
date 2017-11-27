static int pidfile_create(void) {
  FILE *file = NULL;

  if (NULL == pidfile)
    pidfile = COLLECTDMON_PIDFILE;

  if (NULL == (file = fopen(pidfile, "w"))) {
    syslog(LOG_ERR, "Error: couldn't open PID-file (%s) for writing: %s",
           pidfile, strerror(errno));
    return -1;
  }

  fprintf(file, "%i\n", (int)getpid());
  fclose(file);
  return 0;
}