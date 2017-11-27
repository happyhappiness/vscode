static int zone_read_procfile(char const *pidstr, char const *name, void *buf,
                              size_t bufsize) {
  int fd;

  char procfile[MAX_PROCFS_PATH];
  (void)snprintf(procfile, sizeof(procfile), "/proc/%s/%s", pidstr, name);
  if ((fd = open(procfile, O_RDONLY)) == -1) {
    return 1;
  }

  if (sread(fd, buf, bufsize) != 0) {
    char errbuf[1024];
    ERROR("zone plugin: Reading \"%s\" failed: %s", procfile,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fd);
    return 1;
  }

  close(fd);
  return 0;
}