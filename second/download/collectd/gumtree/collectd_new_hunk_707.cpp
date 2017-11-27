  FILE *fh;
  const char *file = global_option_get("PIDFile");

  if ((fh = fopen(file, "w")) == NULL) {
    char errbuf[1024];
    ERROR("fopen (%s): %s", file, sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  fprintf(fh, "%i\n", (int)getpid());
  fclose(fh);

  return 0;
} /* static int pidfile_create (const char *file) */

static int pidfile_remove(void) {
  const char *file = global_option_get("PIDFile");
  if (file == NULL)
    return 0;

  return unlink(file);
} /* static int pidfile_remove (const char *file) */
#endif /* COLLECT_DAEMON */

#ifdef KERNEL_LINUX
static int notify_upstart(void) {
  char const *upstart_job = getenv("UPSTART_JOB");
