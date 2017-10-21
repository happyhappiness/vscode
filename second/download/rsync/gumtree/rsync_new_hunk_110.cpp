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
