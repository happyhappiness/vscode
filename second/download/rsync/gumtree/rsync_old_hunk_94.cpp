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
