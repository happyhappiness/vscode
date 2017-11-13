void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
  struct stat st;
  struct map_struct *buf;
  struct sum_struct *s;
  int statret;
  struct file_struct *file = flist->files[i];

  if (verbose > 2)
    fprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);

  statret = link_stat(fname,&st);

  if (S_ISDIR(file->mode)) {
    if (dry_run) return;
    if (statret == 0 && !S_ISDIR(st.st_mode)) {
      if (do_unlink(fname) != 0) {
	fprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
	return;
      }
      statret = -1;
    }
    if (statret != 0 && do_mkdir(fname,file->mode) != 0 && errno != EEXIST) {
	    if (!(relative_paths && errno==ENOENT && 
		  create_directory_path(fname)==0 && 
		  do_mkdir(fname,file->mode)==0)) {
		    fprintf(FERROR,"mkdir %s : %s (2)\n",
			    fname,strerror(errno));
	    }
    }
    if (set_perms(fname,file,NULL,0) && verbose) 
      fprintf(FINFO,"%s/\n",fname);
    return;
  }

  if (preserve_links && S_ISLNK(file->mode)) {
#if SUPPORT_LINKS
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
    delete_file(fname);
    if (do_symlink(file->link,fname) != 0) {
      fprintf(FERROR,"link %s -> %s : %s\n",
	      fname,file->link,strerror(errno));
    } else {
      set_perms(fname,file,NULL,0);
      if (verbose) 
	fprintf(FINFO,"%s -> %s\n",
		fname,file->link);
    }
#endif
    return;
  }

#ifdef HAVE_MKNOD
  if (am_root && preserve_devices && IS_DEVICE(file->mode)) {
    if (statret != 0 || 
	st.st_mode != file->mode ||
	st.st_rdev != file->rdev) {	
      delete_file(fname);
      if (verbose > 2)
	fprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
		fname,(int)file->mode,(int)file->rdev);
      if (do_mknod(fname,file->mode,file->rdev) != 0) {
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
      fprintf(FINFO,"%s is a hard link\n",f_name(file));
    return;
  }

  if (!S_ISREG(file->mode)) {
    fprintf(FINFO,"skipping non-regular file %s\n",fname);
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
    if (delete_file(fname) != 0) {
      return;
    }

    /* now pretend the file didn't exist */
    write_int(f_out,i);
    if (!dry_run) send_sums(NULL,f_out);    
    return;
  }

  if (update_only && st.st_mtime > file->modtime) {
    if (verbose > 1)
      fprintf(FINFO,"%s is newer\n",fname);
    return;
  }

  if (skip_file(fname, file, &st)) {
    set_perms(fname,file,&st,1);
    return;
  }

  if (dry_run) {
    write_int(f_out,i);
    return;
  }

  if (whole_file) {
    write_int(f_out,i);
    send_sums(NULL,f_out);    
    return;
  }

  /* open the file */  
  fd = open(fname,O_RDONLY);

  if (fd == -1) {
    fprintf(FERROR,"failed to open %s : %s\n",fname,strerror(errno));
    fprintf(FERROR,"skipping %s\n",fname);
    return;
  }

  if (st.st_size > 0) {
    buf = map_file(fd,st.st_size);
  } else {
    buf = NULL;
  }

  if (verbose > 3)
    fprintf(FINFO,"gen mapped %s of size %d\n",fname,(int)st.st_size);

  s = generate_sums(buf,st.st_size,adapt_block_size(file, block_size));

  if (verbose > 2)
    fprintf(FINFO,"sending sums for %d\n",i);

  write_int(f_out,i);
  send_sums(s,f_out);
  write_flush(f_out);

  close(fd);
  if (buf) unmap_file(buf);

  free_sums(s);
}