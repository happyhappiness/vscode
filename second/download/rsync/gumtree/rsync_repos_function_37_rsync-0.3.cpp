void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
  struct stat st;
  char *buf;
  struct sum_struct *s;
  char sum[SUM_LENGTH];
  int statret;

  if (verbose > 2)
    fprintf(stderr,"recv_generator(%s)\n",fname);

  statret = stat(fname,&st);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(flist->files[i].mode)) {
    char lnk[MAXPATHLEN];
    int l;
    if (statret == 0) {
      l = readlink(fname,lnk,MAXPATHLEN-1);
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

  if (!S_ISREG(flist->files[i].mode)) {
    fprintf(stderr,"skipping non-regular file %s\n",fname);
    return;
  }

  if (statret == -1) {
    if (errno == ENOENT) {
      write_int(f_out,i);
      if (!dry_run) send_sums(NULL,f_out);
    } else {
      if (verbose > 1)
	fprintf(stderr,"recv_generator failed to open %s\n",fname);
    }
    return;
  }

  if (!S_ISREG(st.st_mode)) {
    fprintf(stderr,"%s : not a regular file\n",fname);
    return;
  }

  if (update_only && st.st_mtime >= flist->files[i].modtime) {
    if (verbose > 1)
      fprintf(stderr,"%s is newer\n",fname);
    return;
  }

  if (always_checksum && S_ISREG(st.st_mode)) {
    file_checksum(fname,sum,st.st_size);
  }

  if ((st.st_size == flist->files[i].length &&
       ((!preserve_perms || st.st_mtime == flist->files[i].modtime) ||
	(S_ISREG(st.st_mode) && 
	 always_checksum && memcmp(sum,flist->files[i].sum,SUM_LENGTH) == 0)))) {
    if (verbose > 1)
      fprintf(stderr,"%s is uptodate\n",fname);
    return;
  }

  if (dry_run) {
    write_int(f_out,i);
    return;
  }

  /* open the file */  
  fd = open(fname,O_RDONLY);

  if (fd == -1) {
    fprintf(stderr,"failed to open %s : %s\n",fname,strerror(errno));
    return;
  }

  if (st.st_size > 0) {
    buf = map_file(fd,st.st_size);
    if (!buf) {
      fprintf(stderr,"mmap : %s\n",strerror(errno));
      close(fd);
      return;
    }
  } else {
    buf = NULL;
  }

  if (verbose > 3)
    fprintf(stderr,"mapped %s of size %d\n",fname,(int)st.st_size);

  s = generate_sums(buf,st.st_size,BLOCK_SIZE);

  write_int(f_out,i);
  send_sums(s,f_out);
  write_flush(f_out);

  close(fd);
  unmap_file(buf,st.st_size);

  free_sums(s);
}