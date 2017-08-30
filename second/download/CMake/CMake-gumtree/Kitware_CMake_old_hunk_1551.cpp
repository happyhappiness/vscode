{

  char realpath[TAR_MAXPATHLEN];

  char savepath[TAR_MAXPATHLEN];

#if !defined(_WIN32) || defined(__CYGWIN__)

  struct dirent *dent;

  DIR *dp;

#else  

  kwDirEntry * dent;

  kwDirectory *dp;

#endif  

  struct stat s;



#ifdef DEBUG

  printf("==> tar_append_tree(0x%lx, \"%s\", \"%s\")\n",

