  printf("  ==> extracting: %s (character device %ld,%ld)\n",
         filename, devmaj, devmin);
#endif
#ifndef WIN32
  if (mknod(filename, mode | S_IFCHR,
      compat_makedev(devmaj, devmin)) == -1)
#else
