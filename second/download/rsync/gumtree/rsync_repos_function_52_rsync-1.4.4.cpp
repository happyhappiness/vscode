static void set_perms(char *fname,struct file_struct *file,struct stat *st,
		      int report)
{
  int updated = 0;
  struct stat st2;

  if (dry_run) return;

  if (!st) {
    if (stat(fname,&st2) != 0) {
      fprintf(stderr,"stat %s : %s\n",fname,strerror(errno));
      return;
    }
    st = &st2;
  }

  if (preserve_times && !S_ISLNK(st->st_mode) &&
      st->st_mtime != file->modtime) {
    updated = 1;
    if (set_modtime(fname,file->modtime) != 0) {
      fprintf(stderr,"failed to set times on %s : %s\n",
	      fname,strerror(errno));
      return;
    }
  }

#ifdef HAVE_CHMOD
  if (preserve_perms && !S_ISLNK(st->st_mode) &&
      st->st_mode != file->mode) {
    updated = 1;
    if (chmod(fname,file->mode) != 0) {
      fprintf(stderr,"failed to set permissions on %s : %s\n",
	      fname,strerror(errno));
      return;
    }
  }
#endif

  if ((preserve_uid && st->st_uid != file->uid) || 
      (preserve_gid && st->st_gid != file->gid)) {
    updated = 1;
    if (chown(fname,
	      preserve_uid?file->uid:-1,
	      preserve_gid?file->gid:-1) != 0) {
      if (verbose>1 || preserve_uid)
	fprintf(stderr,"chown %s : %s\n",fname,strerror(errno));
      return;
    }
  }
    
  if (verbose > 1 && report) {
    if (updated)
      fprintf(am_server?stderr:stdout,"%s\n",fname);
    else
      fprintf(am_server?stderr:stdout,"%s is uptodate\n",fname);
  }
}