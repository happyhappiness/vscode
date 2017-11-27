static oconfig_item_t *cf_read_generic(const char *path, const char *pattern,
                                       int depth) {
  struct stat statbuf;
  int status;

  if (depth >= CF_MAX_DEPTH) {
    ERROR("configfile: Not including `%s' because the maximum "
          "nesting depth has been reached.",
          path);
    return NULL;
  }

  status = stat(path, &statbuf);
  if (status != 0) {
    char errbuf[1024];
    ERROR("configfile: stat (%s) failed: %s", path,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return NULL;
  }

  if (S_ISREG(statbuf.st_mode))
    return cf_read_file(path, pattern, depth);
  else if (S_ISDIR(statbuf.st_mode))
    return cf_read_dir(path, pattern, depth);

  ERROR("configfile: %s is neither a file nor a directory.", path);
  return NULL;
}