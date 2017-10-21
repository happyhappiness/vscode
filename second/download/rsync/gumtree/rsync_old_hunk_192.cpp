

void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
  struct stat st;
  char *buf;
  struct sum_struct *s;
  char sum[SUM_LENGTH];
  int statret;
  struct file_struct *file = &flist->files[i];

  if (verbose > 2)
    fprintf(FERROR,"recv_generator(%s)\n",fname);

  statret = lstat(fname,&st);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    char lnk[MAXPATHLEN];
