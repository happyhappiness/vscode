  s->flength = offset;

  return s;
}


static int set_perms(char *fname,struct file_struct *file,struct stat *st,
		     int report)
{
  int updated = 0;
  struct stat st2;

  if (dry_run) return 0;

  if (!st) {
    if (lstat(fname,&st2) != 0) {
      fprintf(FERROR,"stat %s : %s\n",fname,strerror(errno));
      return 0;
    }
    st = &st2;
  }

  if (preserve_times && !S_ISLNK(st->st_mode) &&
      st->st_mtime != file->modtime) {
    updated = 1;
    if (set_modtime(fname,file->modtime) != 0) {
      fprintf(FERROR,"failed to set times on %s : %s\n",
	      fname,strerror(errno));
      return 0;
    }
  }

#ifdef HAVE_CHMOD
  if (preserve_perms && !S_ISLNK(st->st_mode) &&
      st->st_mode != file->mode) {
    updated = 1;
    if (chmod(fname,file->mode) != 0) {
      fprintf(FERROR,"failed to set permissions on %s : %s\n",
	      fname,strerror(errno));
      return 0;
    }
  }
#endif

  if ((am_root && preserve_uid && st->st_uid != file->uid) || 
      (preserve_gid && st->st_gid != file->gid)) {
    updated = 1;
    if (chown(fname,
	      (am_root&&preserve_uid)?file->uid:-1,
	      preserve_gid?file->gid:-1) != 0) {
      if (verbose>1 || preserve_uid)
	fprintf(FERROR,"chown %s : %s\n",fname,strerror(errno));
      return updated;
    }
  }
    
  if (verbose > 1 && report) {
    if (updated)
      fprintf(FINFO,"%s\n",fname);
    else
      fprintf(FINFO,"%s is uptodate\n",fname);
  }
  return updated;
}


void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
