static int pidfile_create(void) {
  FILE *fh;
  const char *file = global_option_get("PIDFile");

  if ((fh = fopen(file, "w")) == NULL) {
    char errbuf[1024];
    ERROR("fopen (%s): %s", file, sstrerror(errno, errbuf, sizeof(errbuf)));
    return (1);
  }

  fprintf(fh, "%i\n", (int)getpid());
  fclose(fh);

  return (0);
}