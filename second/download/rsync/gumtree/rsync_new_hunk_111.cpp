    int l;
    if (statret == 0) {
      l = readlink(fname,lnk,MAXPATHLEN-1);
      if (l > 0) {
	lnk[l] = 0;
	if (strcmp(lnk,flist->files[i].link) == 0) {
	  set_perms(fname,&flist->files[i],&st,1);
	  return;
	}
      }
    }
    if (!dry_run) unlink(fname);
    if (!dry_run && symlink(flist->files[i].link,fname) != 0) {
      fprintf(stderr,"link %s -> %s : %s\n",
	      fname,flist->files[i].link,strerror(errno));
    } else {
      set_perms(fname,&flist->files[i],NULL,0);
      if (verbose) 
	fprintf(am_server?stderr:stdout,"%s -> %s\n",
		fname,flist->files[i].link);
    }
    return;
  }
#endif

#ifdef HAVE_MKNOD
