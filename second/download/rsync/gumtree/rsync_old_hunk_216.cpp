
  if (verbose > 2)
    fprintf(FERROR,"recv_generator(%s,%d)\n",fname,i);

  statret = lstat(fname,&st);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    char lnk[MAXPATHLEN];
    int l;
    if (statret == 0) {
      l = readlink(fname,lnk,MAXPATHLEN-1);
