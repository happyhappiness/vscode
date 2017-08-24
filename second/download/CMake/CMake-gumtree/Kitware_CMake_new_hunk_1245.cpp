  buf[sizeof(buf)-1] = 0;

  if (mkdirhier(dirname(buf)) == -1)
    {
    if (pathname)
      {
      free(pathname);
      }
    return -1;
    }

#ifdef DEBUG
  printf("  ==> extracting: %s (character device %ld,%ld)\n",
