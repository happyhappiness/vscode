  char *filename;

  char buf[TAR_MAXPATHLEN];

  int i;

  char *pathname = 0;



#ifdef DEBUG

  printf("==> tar_extract_all(TAR *t, \"%s\")\n",

