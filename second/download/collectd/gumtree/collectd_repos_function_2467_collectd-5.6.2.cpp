static int change_basedir(const char *orig_dir) {
  char *dir;
  size_t dirlen;
  int status;

  dir = strdup(orig_dir);
  if (dir == NULL) {
    char errbuf[1024];
    ERROR("strdup failed: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  dirlen = strlen(dir);
  while ((dirlen > 0) && (dir[dirlen - 1] == '/'))
    dir[--dirlen] = '\0';

  if (dirlen == 0) {
    free(dir);
    return (-1);
  }

  status = chdir(dir);
  if (status == 0) {
    free(dir);
    return (0);
  } else if (errno != ENOENT) {
    char errbuf[1024];
    ERROR("change_basedir: chdir (%s): %s", dir,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    free(dir);
    return (-1);
  }

  status = mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
  if (status != 0) {
    char errbuf[1024];
    ERROR("change_basedir: mkdir (%s): %s", dir,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    free(dir);
    return (-1);
  }

  status = chdir(dir);
  if (status != 0) {
    char errbuf[1024];
    ERROR("change_basedir: chdir (%s): %s", dir,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    free(dir);
    return (-1);
  }

  free(dir);
  return (0);
}