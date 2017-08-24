#endif

  filename = (realname ? realname : th_get_pathname(t));
  if (mkdirhier(dirname(filename)) == -1)
    return -1;

  if (unlink(filename) == -1 && errno != ENOENT)
    return -1;

#ifdef DEBUG
  printf("  ==> extracting: %s (symlink to %s)\n",
