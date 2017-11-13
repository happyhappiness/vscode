static struct file_struct *make_file(int recurse,char *fname)
{
  static struct file_struct file;
  struct stat st;
  char sum[SUM_LENGTH];

  bzero(sum,SUM_LENGTH);

  if (lstat(fname,&st) != 0) {
    fprintf(stderr,"%s: %s\n",
	    fname,strerror(errno));
    return NULL;
  }

  if (S_ISDIR(st.st_mode) && !recurse) {
    fprintf(stderr,"skipping directory %s\n",fname);
    return NULL;
  }

  if (one_file_system && st.st_dev != filesystem_dev)
    return NULL;

  if (!match_file_name(fname,&st))
    return NULL;

  if (verbose > 2)
    fprintf(stderr,"make_file(%s)\n",fname);

  file.name = strdup(fname);
  file.modtime = st.st_mtime;
  file.length = st.st_size;
  file.mode = st.st_mode;
  file.uid = st.st_uid;
  file.gid = st.st_gid;
#ifdef HAVE_ST_RDEV
  file.dev = st.st_rdev;
#endif

#if SUPPORT_LINKS
  if (S_ISLNK(st.st_mode)) {
    int l;
    char lnk[MAXPATHLEN];
    if ((l=readlink(fname,lnk,MAXPATHLEN-1)) == -1) {
      fprintf(stderr,"readlink %s : %s\n",fname,strerror(errno));
      return NULL;
    }
    lnk[l] = 0;
    file.link = strdup(lnk);
  }
#endif

  if (always_checksum && S_ISREG(st.st_mode)) {
    file_checksum(fname,file.sum,st.st_size);
  }       

  if (flist_dir)
    file.dir = strdup(flist_dir);
  else
    file.dir = NULL;

  if (!S_ISDIR(st.st_mode))
    total_size += st.st_size;

  return &file;
}