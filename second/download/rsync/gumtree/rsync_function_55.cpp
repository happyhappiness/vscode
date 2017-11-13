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

#ifdef HAVE_UTIME
  if (preserve_times && st->st_mtime != file->modtime) {
    struct utimbuf tbuf;  
    updated = 1;
    tbuf.actime = time(NULL);
    tbuf.modtime = file->modtime;
    if (utime(fname,&tbuf) != 0) {
      fprintf(stderr,"failed to set times on %s : %s\n",
	      fname,strerror(errno));
      return;
    }
  }
#endif

#ifdef HAVE_CHMOD
  if (preserve_perms && st->st_mode != file->mode) {
    updated = 1;
    if (chmod(fname,file->mode) != 0) {
      fprintf(stderr,"failed to set permissions on %s : %s\n",
	      fname,strerror(errno));
      return;
    }
  }
#endif

#ifdef HAVE_CHOWN
  if ((preserve_uid && st->st_uid != file->uid) || 
      (preserve_gid && st->st_gid != file->gid) {
    updated = 1;
    if (chown(fname,
	      preserve_uid?file->uid:-1,
	      preserve_gid?file->gid:-1) != 0) {
      fprintf(stderr,"chown %s : %s\n",fname,strerror(errno));
      return;
    }
  }
#endif

  if (verbose > 1 && report) {
    if (updated)
      fprintf(am_server?stderr:stdout,"%s\n",fname);
    else
      fprintf(am_server?stderr:stdout,"%s is uptodate\n",fname);
  }
}