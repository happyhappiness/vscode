  char *filename;
  char buf[TAR_MAXPATHLEN];
  int i;

  while ((i = th_read(t)) == 0)
  {
    filename = th_get_pathname(t);
    if (fnmatch(globname, filename, FNM_PATHNAME | FNM_PERIOD))
    {
      if (TH_ISREG(t) && tar_skip_regfile(t))
        return -1;
      continue;
    }
    if (t->options & TAR_VERBOSE)
      th_print_long_ls(t);
    if (prefix != NULL)
      snprintf(buf, sizeof(buf), "%s/%s", prefix, filename);
    else
      strlcpy(buf, filename, sizeof(buf));
    if (tar_extract_file(t, filename) != 0)
      return -1;
  }

  return (i == 1 ? 0 : -1);
