  tar_ino_t *ti = NULL;

#if !defined(_WIN32) || defined(__CYGWIN__)

  int i;

#else

  size_t plen;

#endif

  char path[TAR_MAXPATHLEN];



#ifdef DEBUG

  printf("==> tar_append_file(TAR=0x%lx (\"%s\"), realname=\"%s\", "

