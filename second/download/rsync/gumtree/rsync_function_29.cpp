int recv_files(int f_in,struct file_list *flist,char *local_name)
{  
  int fd1,fd2;
  struct stat st;
  char *fname;
  char fnametmp[MAXPATHLEN];
  char *buf;
  int i;

  if (verbose > 2)
    fprintf(stderr,"recv_files(%d) starting\n",flist->count);

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) break;

      fname = flist->files[i].name;

      if (local_name)
	fname = local_name;

      if (verbose > 2)
	fprintf(stderr,"recv_files(%s)\n",fname);

      /* open the file */  
      fd1 = open(fname,O_RDONLY|O_CREAT,flist->files[i].mode);

      if (fd1 == -1) {
	fprintf(stderr,"recv_files failed to open %s\n",fname);
	return -1;
      }

      if (fstat(fd1,&st) != 0) {
	fprintf(stderr,"fstat %s : %s\n",fname,strerror(errno));
	close(fd1);
	return -1;
      }

      if (!S_ISREG(st.st_mode)) {
	fprintf(stderr,"%s : not a regular file\n",fname);
	close(fd1);
	return -1;
      }

      if (st.st_size > 0) {
	buf = map_file(fd1,st.st_size);
	if (!buf) return -1;
      } else {
	buf = NULL;
      }

      if (verbose > 2)
	fprintf(stderr,"mapped %s of size %d\n",fname,(int)st.st_size);

      /* open tmp file */
      sprintf(fnametmp,"%s.XXXXXX",fname);
      if (NULL == mktemp(fnametmp)) 
	return -1;
      fd2 = open(fnametmp,O_WRONLY|O_CREAT,st.st_mode);
      if (fd2 == -1) return -1;

      if (verbose)
	fprintf(stderr,"%s\n",fname);

      /* recv file data */
      receive_data(f_in,buf,fd2);

      close(fd1);
      close(fd2);

      if (verbose > 2)
	fprintf(stderr,"renaming %s to %s\n",fnametmp,fname);

      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	sprintf(fnamebak,"%s%s",fname,backup_suffix);
	if (rename(fname,fnamebak) != 0) {
	  fprintf(stderr,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
	  exit(1);
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	fprintf(stderr,"rename %s -> %s : %s\n",fnametmp,fname,strerror(errno));
      }

      unmap_file(buf,st.st_size);

      set_perms(fname,&flist->files[i]);
    }

  if (verbose > 2)
    fprintf(stderr,"recv_files finished\n");
  
  return 0;
}