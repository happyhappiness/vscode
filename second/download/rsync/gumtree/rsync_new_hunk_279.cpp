  static struct file_struct file;
  struct stat st;
  char sum[SUM_LENGTH];

  bzero(sum,SUM_LENGTH);

  if (link_stat(fname,&st) != 0) {
    fprintf(FERROR,"%s: %s\n",
	    fname,strerror(errno));
    return NULL;
  }

  if (S_ISDIR(st.st_mode) && !recurse) {
