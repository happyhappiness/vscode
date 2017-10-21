      (preserve_gid && st->st_gid != file->gid)) {
    updated = 1;
    if (chown(fname,
	      preserve_uid?file->uid:-1,
	      preserve_gid?file->gid:-1) != 0) {
      if (verbose>1 || preserve_uid)
	fprintf(FERROR,"chown %s : %s\n",fname,strerror(errno));
      return;
    }
  }
    
  if (verbose > 1 && report) {
    if (updated)
      fprintf(FINFO,"%s\n",fname);
    else
      fprintf(FINFO,"%s is uptodate\n",fname);
  }
}


void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
  struct stat st;
  char *buf;
  struct sum_struct *s;
  char sum[SUM_LENGTH];
  int statret;
  struct file_struct *file = &flist->files[i];

  if (verbose > 2)
    fprintf(FERROR,"recv_generator(%s)\n",fname);

  statret = lstat(fname,&st);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    char lnk[MAXPATHLEN];
    int l;
    if (statret == 0) {
      l = readlink(fname,lnk,MAXPATHLEN-1);
      if (l > 0) {
	lnk[l] = 0;
	if (strcmp(lnk,file->link) == 0) {
	  set_perms(fname,file,&st,1);
	  return;
	}
      }
    }
    if (!dry_run) unlink(fname);
    if (!dry_run && symlink(file->link,fname) != 0) {
      fprintf(FERROR,"link %s -> %s : %s\n",
	      fname,file->link,strerror(errno));
    } else {
      set_perms(fname,file,NULL,0);
      if (verbose) 
	fprintf(FINFO,"%s -> %s\n",
		fname,file->link);
    }
    return;
  }
#endif

#ifdef HAVE_MKNOD
  if (preserve_devices && IS_DEVICE(file->mode)) {
    if (statret != 0 || 
	st.st_mode != file->mode ||
	st.st_rdev != file->rdev) {	
      if (!dry_run) unlink(fname);
      if (verbose > 2)
	fprintf(FERROR,"mknod(%s,0%o,0x%x)\n",
		fname,(int)file->mode,(int)file->rdev);
      if (!dry_run && 
	  mknod(fname,file->mode,file->rdev) != 0) {
	fprintf(FERROR,"mknod %s : %s\n",fname,strerror(errno));
      } else {
	set_perms(fname,file,NULL,0);
	if (verbose)
	  fprintf(FINFO,"%s\n",fname);
      }
    } else {
      set_perms(fname,file,&st,1);
    }
    return;
  }
#endif

  if (preserve_hard_links && check_hard_link(file)) {
    if (verbose > 1)
      fprintf(FINFO,"%s is a hard link\n",file->name);
    return;
  }

  if (!S_ISREG(file->mode)) {
    fprintf(FERROR,"skipping non-regular file %s\n",fname);
    return;
  }

  if (statret == -1) {
    if (errno == ENOENT) {
      write_int(f_out,i);
      if (!dry_run) send_sums(NULL,f_out);
    } else {
      if (verbose > 1)
	fprintf(FERROR,"recv_generator failed to open %s\n",fname);
    }
    return;
  }

  if (!S_ISREG(st.st_mode)) {
    fprintf(FERROR,"%s : not a regular file\n",fname);
    return;
  }

  if (update_only && st.st_mtime >= file->modtime) {
    if (verbose > 1)
      fprintf(FERROR,"%s is newer\n",fname);
    return;
  }

  if (always_checksum && S_ISREG(st.st_mode)) {
    file_checksum(fname,sum,st.st_size);
  }

  if (st.st_size == file->length &&
      ((!ignore_times && st.st_mtime == file->modtime) ||
       (always_checksum && S_ISREG(st.st_mode) && 	  
	memcmp(sum,file->sum,csum_length) == 0))) {
    set_perms(fname,file,&st,1);
    return;
  }

  if (dry_run) {
    write_int(f_out,i);
    return;
  }

  /* open the file */  
  fd = open(fname,O_RDONLY);

  if (fd == -1) {
    fprintf(FERROR,"failed to open %s : %s\n",fname,strerror(errno));
    return;
  }

  if (st.st_size > 0) {
    buf = map_file(fd,st.st_size);
  } else {
    buf = NULL;
  }

  if (verbose > 3)
    fprintf(FERROR,"mapped %s of size %d\n",fname,(int)st.st_size);

  s = generate_sums(buf,st.st_size,block_size);

  write_int(f_out,i);
  send_sums(s,f_out);
  write_flush(f_out);
