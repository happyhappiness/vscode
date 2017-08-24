    return -1;
    }

#ifdef DEBUG
  printf("  ==> extracting: %s (mode %04o, directory)\n", filename,
         mode);
#endif
#ifdef WIN32
  if (mkdir(filename) == -1)
#else
  if (mkdir(filename, mode) == -1)
#endif
  {
#ifdef __BORLANDC__
