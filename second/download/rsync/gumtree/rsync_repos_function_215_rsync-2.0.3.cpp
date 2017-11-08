static char *get_local_name(struct file_list *flist,char *name)
{
	STRUCT_STAT st;
	extern int orig_umask;

  if (do_stat(name,&st) == 0) {
    if (S_ISDIR(st.st_mode)) {
      if (chdir(name) != 0) {
	rprintf(FERROR,"chdir %s : %s (1)\n",name,strerror(errno));
	exit_cleanup(1);
      }
      return NULL;
    }
    if (flist->count > 1) {
      rprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
      exit_cleanup(1);
    }
    return name;
  }

  if (flist->count == 1)
    return name;

  if (!name) 
    return NULL;

  if (do_mkdir(name,0777 & ~orig_umask) != 0) {
    rprintf(FERROR,"mkdir %s : %s (1)\n",name,strerror(errno));
    exit_cleanup(1);
  } else {
    rprintf(FINFO,"created directory %s\n",name);
  }

  if (chdir(name) != 0) {
    rprintf(FERROR,"chdir %s : %s (2)\n",name,strerror(errno));
    exit_cleanup(1);
  }

  return NULL;
}