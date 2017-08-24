#endif

  filename = (realname ? realname : th_get_pathname(t));

  /* Make a copy of the string because dirname and mkdirhier may modify the
   * string */
  strncpy(buf, filename, sizeof(buf)-1);
  buf[sizeof(buf)-1] = 0;

  if (mkdirhier(dirname(buf)) == -1)
    return -1;

  if (unlink(filename) == -1 && errno != ENOENT)
    {
    return -1;
    }

#ifdef DEBUG
  printf("  ==> extracting: %s (symlink to %s)\n",
