	return ret;
}

void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
  STRUCT_STAT st;
  struct map_struct *buf;
  struct sum_struct *s;
  int statret;
  struct file_struct *file = flist->files[i];

  if (verbose > 2)
    rprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);

  statret = link_stat(fname,&st);

  if (S_ISDIR(file->mode)) {
    if (dry_run) return;
    if (statret == 0 && !S_ISDIR(st.st_mode)) {
      if (do_unlink(fname) != 0) {
	rprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
	return;
      }
      statret = -1;
    }
    if (statret != 0 && do_mkdir(fname,file->mode) != 0 && errno != EEXIST) {
	    if (!(relative_paths && errno==ENOENT && 
		  create_directory_path(fname)==0 && 
		  do_mkdir(fname,file->mode)==0)) {
		    rprintf(FERROR,"mkdir %s : %s (2)\n",
			    fname,strerror(errno));
	    }
    }
    if (set_perms(fname,file,NULL,0) && verbose) 
      rprintf(FINFO,"%s/\n",fname);
    return;
  }

  if (preserve_links && S_ISLNK(file->mode)) {
#if SUPPORT_LINKS
    char lnk[MAXPATHLEN];
