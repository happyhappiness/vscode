static int read_cpuacct_root(const char *dirname, const char *filename,
                             void *user_data) {
  char abs_path[PATH_MAX];
  struct stat statbuf;
  int status;

  snprintf(abs_path, sizeof(abs_path), "%s/%s", dirname, filename);

  status = lstat(abs_path, &statbuf);
  if (status != 0) {
    ERROR("cgroups plugin: stat (%s) failed.", abs_path);
    return -1;
  }

  if (S_ISDIR(statbuf.st_mode)) {
    status = walk_directory(abs_path, read_cpuacct_procs,
                            /* user_data = */ NULL,
                            /* include_hidden = */ 0);
    return status;
  }

  return 0;
}