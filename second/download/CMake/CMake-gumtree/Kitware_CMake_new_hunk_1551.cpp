{
  char realpath[TAR_MAXPATHLEN];
  char savepath[TAR_MAXPATHLEN];
  size_t plen;
#if defined(HAVE_DIRENT_H)
  struct dirent *dent;
  DIR *dp;
#else  
  kwDirEntry * dent;
  kwDirectory *dp;
#endif  
  struct stat s;
  strncpy(realpath, realdir, sizeof(realpath));
  realpath[sizeof(realpath)-1] = 0;
  plen = strlen(realpath);
  if ( realpath[plen-1] == '/' )
    {
    realpath[plen-1] = 0;
    }
  

#ifdef DEBUG
  printf("==> tar_append_tree(0x%lx, \"%s\", \"%s\")\n",
