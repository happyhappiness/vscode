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
