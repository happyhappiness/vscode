  tar_ino_t *ti = NULL;
#if !defined(_WIN32) || defined(__CYGWIN__)
  int i;
  char path[TAR_MAXPATHLEN];
#endif

#ifdef DEBUG
  printf("==> tar_append_file(TAR=0x%lx (\"%s\"), realname=\"%s\", "
