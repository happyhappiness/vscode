static int set_perms(char *fname,struct file_struct *file,STRUCT_STAT *st,
		     int report)
{
  int updated = 0;
  STRUCT_STAT st2;

  if (dry_run) return 0;

  if (!st) {
    if (link_stat(fname,&st2) != 0) {
      rprintf(FERROR,"stat %s : %s\n",fname,strerror(errno));
      return 0;
    }
    st = &st2;
  }

  if (preserve_times && !S_ISLNK(st->st_mode) &&
      st->st_mtime != file->modtime) {
    updated = 1;
    if (set_modtime(fname,file->modtime) != 0) {
      rprintf(FERROR,"failed to set times on %s : %s\n",
	      fname,strerror(errno));
      return 0;
    }
  }

#ifdef HAVE_CHMOD
  if (preserve_perms && !S_ISLNK(st->st_mode) &&
      st->st_mode != file->mode) {
    updated = 1;
    if (do_chmod(fname,file->mode) != 0) {
      rprintf(FERROR,"failed to set permissions on %s : %s\n",
	      fname,strerror(errno));
      return 0;
    }
  }
#endif

  if ((am_root && preserve_uid && st->st_uid != file->uid) || 
      (preserve_gid && st->st_gid != file->gid)) {
	  if (do_lchown(fname,
			(am_root&&preserve_uid)?file->uid:-1,
			preserve_gid?file->gid:-1) != 0) {
		  if (preserve_uid && st->st_uid != file->uid)
			  updated = 1;
		  if (verbose>1 || preserve_uid)
			  rprintf(FERROR,"chown %s : %s\n",
				  fname,strerror(errno));
		  return updated;
	  }
	  updated = 1;
  }
    
  if (verbose > 1 && report) {
	  if (updated)
		  rprintf(FINFO,"%s\n",fname);
	  else
		  rprintf(FINFO,"%s is uptodate\n",fname);
  }
  return updated;
}