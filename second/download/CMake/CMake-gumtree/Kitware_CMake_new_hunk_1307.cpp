#ifdef DEBUG
  printf("  ==> extracting: %s (fifo)\n", filename);
#endif
#if !defined(WIN32) && !defined(__VMS)
  if (mkfifo(filename, mode & 07777) == -1)
#else
    (void)mode;