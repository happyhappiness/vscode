int write_pidfile(const char *filename)
{
  FILE *pidfile;
  long pid;

  pid = (long)getpid();
  pidfile = fopen(filename, "w");
  if(!pidfile) {
    logmsg("Couldn't write pid file: %s %s", filename, strerror(ERRNO));
    return 0; /* fail */
  }
  fprintf(pidfile, "%ld\n", pid);
  fclose(pidfile);
  logmsg("Wrote pid %ld to %s", pid, filename);
  return 1; /* success */
}