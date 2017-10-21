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
    } else {
      if (verbose) 
	fprintf(am_server?stderr:stdout,"%s -> %s\n",fname,flist->files[i].link);
    }
    return;
  }
#endif

#ifdef HAVE_MKNOD
  if (preserve_devices && 
      (S_ISCHR(flist->files[i].mode) || S_ISBLK(flist->files[i].mode))) {
    if (statret != 0 || 
	st.st_mode != flist->files[i].mode ||
	st.st_rdev != flist->files[i].dev) {	
      if (!dry_run) unlink(fname);
      if (verbose > 2)
	fprintf(stderr,"mknod(%s,0%o,0x%x)\n",
		fname,(int)flist->files[i].mode,(int)flist->files[i].dev);
      if (!dry_run && mknod(fname,flist->files[i].mode,flist->files[i].dev) != 0) {
	fprintf(stderr,"mknod %s : %s\n",fname,strerror(errno));
      } else {
	if (verbose)
	  fprintf(am_server?stderr:stdout,"%s\n",fname);
	set_perms(fname,&flist->files[i]);
      }
    }
    return;
  }
#endif
