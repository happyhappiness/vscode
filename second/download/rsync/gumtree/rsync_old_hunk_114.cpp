  char **list=list1;
  FILE *f = fopen(fname,"r");
  char line[MAXPATHLEN];
  if (!f) {
    if (fatal) {
      fprintf(stderr,"%s : %s\n",fname,strerror(errno));
      exit(1);
    }
    return list;
  }

  while (fgets(line,MAXPATHLEN,f)) {
    int l = strlen(line);
