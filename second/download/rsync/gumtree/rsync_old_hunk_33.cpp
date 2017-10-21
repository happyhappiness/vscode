  char sum[SUM_LENGTH];
  int statret;

  if (verbose > 2)
    fprintf(stderr,"recv_generator(%s)\n",fname);

  statret = stat(fname,&st);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(flist->files[i].mode)) {
    char lnk[MAXPATHLEN];
    int l;
    if (statret == 0) {
      l = readlink(fname,lnk,MAXPATHLEN-1);
      if (l > 0) {
	lnk[l] = 0;
	if (strcmp(lnk,flist->files[i].link) == 0)
	  return;
      }
    }
    if (!dry_run) unlink(fname);
    if (!dry_run && symlink(flist->files[i].link,fname) != 0) {
      fprintf(stderr,"link %s -> %s : %s\n",
	      fname,flist->files[i].link,strerror(errno));
