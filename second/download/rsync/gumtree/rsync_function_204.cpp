int recv_files(int f_in,struct file_list *flist,char *local_name)
{  
  int fd1,fd2;
  struct stat st;
  char *fname;
  char fnametmp[MAXPATHLEN];
  char *buf;
  int i;

  if (verbose > 2) {
    fprintf(stderr,"recv_files(%d) starting\n",flist->count);
  }

  if (recurse && delete_mode && !local_name && flist->count>0) {
    delete_files(flist);
  }

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) break;

      fname = flist->files[i].name;

      if (local_name)
	fname = local_name;

      if (dry_run) {
	if (!am_server && verbose)
	  printf("%s\n",fname);
	continue;
      }

      if (verbose > 2)
	fprintf(stderr,"recv_files(%s)\n",fname);

      /* open the file */  
      fd1 = open(fname,O_RDONLY);

      if (fd1 != -1 && fstat(fd1,&st) != 0) {
	fprintf(stderr,"fstat %s : %s\n",fname,strerror(errno));
	close(fd1);
	return -1;
      }

      if (fd1 != -1 && !S_ISREG(st.st_mode)) {
	fprintf(stderr,"%s : not a regular file\n",fname);
	close(fd1);
	return -1;
      }

      if (fd1 != -1 && st.st_size > 0) {
	buf = map_file(fd1,st.st_size);
      } else {
	buf = NULL;
      }

      if (verbose > 2)
	fprintf(stderr,"mapped %s of size %d\n",fname,(int)st.st_size);

      /* open tmp file */
      sprintf(fnametmp,"%s.XXXXXX",fname);
      if (NULL == mktemp(fnametmp)) {
	fprintf(stderr,"mktemp %s failed\n",fnametmp);
	return -1;
      }
      fd2 = open(fnametmp,O_WRONLY|O_CREAT,flist->files[i].mode);
      if (fd2 == -1) {
	fprintf(stderr,"open %s : %s\n",fnametmp,strerror(errno));
	return -1;
      }
      
      cleanup_fname = fnametmp;

      if (!am_server && verbose)
	printf("%s\n",fname);

      /* recv file data */
      receive_data(f_in,buf,fd2,fname);

      if (fd1 != -1) {
	unmap_file(buf,st.st_size);
	close(fd1);
      }
      close(fd2);

      if (verbose > 2)
	fprintf(stderr,"renaming %s to %s\n",fnametmp,fname);

      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	sprintf(fnamebak,"%s%s",fname,backup_suffix);
	if (rename(fname,fnamebak) != 0 && errno != ENOENT) {
	  fprintf(stderr,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
	  exit_cleanup(1);
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	fprintf(stderr,"rename %s -> %s : %s\n",
		fnametmp,fname,strerror(errno));
      }

      cleanup_fname = NULL;

      set_perms(fname,&flist->files[i],NULL,0);
    }

  if (verbose > 2)
    fprintf(stderr,"recv_files finished\n");
  
  return 0;
}