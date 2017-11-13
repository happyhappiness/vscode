int recv_files(int f_in,struct file_list *flist,char *local_name,int f_gen)
{  
  int fd1,fd2;
  struct stat st;
  char *fname;
  char fnametmp[MAXPATHLEN];
  struct map_struct *buf;
  int i;
  struct file_struct *file;
  int phase=0;
  int recv_ok;

  if (verbose > 2) {
    fprintf(FERROR,"recv_files(%d) starting\n",flist->count);
  }

  if (recurse && delete_mode && !local_name && flist->count>0) {
    delete_files(flist);
  }

  while (1) 
    {      
      i = read_int(f_in);
      if (i == -1) {
	if (phase==0 && remote_version >= 13) {
	  phase++;
	  csum_length = SUM_LENGTH;
	  if (verbose > 2)
	    fprintf(FERROR,"recv_files phase=%d\n",phase);
	  write_int(f_gen,-1);
	  write_flush(f_gen);
	  continue;
	}
	break;
      }

      file = &flist->files[i];
      fname = file->name;

      if (local_name)
	fname = local_name;

      if (dry_run) {
	if (!am_server && verbose)
	  printf("%s\n",fname);
	continue;
      }

      if (verbose > 2)
	fprintf(FERROR,"recv_files(%s)\n",fname);

      /* open the file */  
      fd1 = open(fname,O_RDONLY);

      if (fd1 != -1 && fstat(fd1,&st) != 0) {
	fprintf(FERROR,"fstat %s : %s\n",fname,strerror(errno));
	receive_data(f_in,NULL,-1,NULL);
	close(fd1);
	continue;
      }

      if (fd1 != -1 && !S_ISREG(st.st_mode)) {
	fprintf(FERROR,"%s : not a regular file (recv_files)\n",fname);
	receive_data(f_in,NULL,-1,NULL);
	close(fd1);
	continue;
      }

      if (fd1 != -1 && st.st_size > 0) {
	buf = map_file(fd1,st.st_size);
	if (verbose > 2)
	  fprintf(FERROR,"recv mapped %s of size %d\n",fname,(int)st.st_size);
      } else {
	buf = NULL;
      }

      /* open tmp file */
      if (strlen(fname) > (MAXPATHLEN-8)) {
	fprintf(FERROR,"filename too long\n");
	continue;
      }
      sprintf(fnametmp,"%s.XXXXXX",fname);
      if (NULL == mktemp(fnametmp)) {
	fprintf(FERROR,"mktemp %s failed\n",fnametmp);
	receive_data(f_in,buf,-1,NULL);
	if (buf) unmap_file(buf);
	close(fd1);
	continue;
      }
      fd2 = open(fnametmp,O_WRONLY|O_CREAT,file->mode);
      if (relative_paths && errno == ENOENT && 
	  create_directory_path(fnametmp) == 0) {
	      fd2 = open(fnametmp,O_WRONLY|O_CREAT,file->mode);
      }
      if (fd2 == -1) {
	fprintf(FERROR,"open %s : %s\n",fnametmp,strerror(errno));
	receive_data(f_in,buf,-1,NULL);
	if (buf) unmap_file(buf);
	close(fd1);
	continue;
      }
      
      cleanup_fname = fnametmp;

      if (!am_server && verbose)
	printf("%s\n",fname);

      /* recv file data */
      recv_ok = receive_data(f_in,buf,fd2,fname);

      if (fd1 != -1) {
	if (buf) unmap_file(buf);
	close(fd1);
      }
      close(fd2);

      if (verbose > 2)
	fprintf(FERROR,"renaming %s to %s\n",fnametmp,fname);

      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
		fprintf(FERROR,"backup filename too long\n");
		continue;
	}
	sprintf(fnamebak,"%s%s",fname,backup_suffix);
	if (rename(fname,fnamebak) != 0 && errno != ENOENT) {
	  fprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
	  continue;
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	fprintf(FERROR,"rename %s -> %s : %s\n",
		fnametmp,fname,strerror(errno));
	unlink(fnametmp);
      }

      cleanup_fname = NULL;

      set_perms(fname,file,NULL,0);

      if (!recv_ok) {
	if (verbose > 1)
	  fprintf(FERROR,"redoing %s(%d)\n",fname,i);
        if (csum_length == SUM_LENGTH)
	  fprintf(FERROR,"ERROR: file corruption in %s\n",fname);
	write_int(f_gen,i);
      }
    }

  if (preserve_hard_links)
	  do_hard_links(flist);

  /* now we need to fix any directory permissions that were 
     modified during the transfer */
  for (i = 0; i < flist->count; i++) {
	  struct file_struct *file = &flist->files[i];
	  if (!file->name || !S_ISDIR(file->mode)) continue;
	  recv_generator(file->name,flist,i,-1);
  }

  if (verbose > 2)
    fprintf(FERROR,"recv_files finished\n");
  
  return 0;
}