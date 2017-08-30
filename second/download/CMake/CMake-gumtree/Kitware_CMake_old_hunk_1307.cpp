#ifdef DEBUG
  printf("  ==> extracting: %s (fifo)\n", filename);
#endif
#ifndef WIN32
  if (mkfifo(filename, mode & 07777) == -1)
#else
    (void)mode;