off_t send_files(struct file_list *flist,int f_out,int f_in)
{ 
  int fd;
  struct sum_struct *s;
  char *buf;
  struct stat st;
  char fname[MAXPATHLEN];  
  off_t total=0;
  int i;

  if (verbose > 2)
    fprintf(stderr,"send_files starting\n");

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) break;

      fname[0] = 0;
      if (flist->files[i].dir) {
	strcpy(fname,flist->files[i].dir);
	strcat(fname,"/");
      }
      strcat(fname,flist->files[i].name);

      if (verbose > 2) 
	fprintf(stderr,"send_files(%d,%s)\n",i,fname);

      if (dry_run) {	
	if (!am_server && verbose)
	  printf("%s\n",fname);
	write_int(f_out,i);
	continue;
      }

      s = receive_sums(f_in);
      if (!s) {
	fprintf(stderr,"receive_sums failed\n");
	return -1;
      }

      fd = open(fname,O_RDONLY);
      if (fd == -1) {
	fprintf(stderr,"send_files failed to open %s: %s\n",
		fname,strerror(errno));
	continue;
      }
  
      /* map the local file */
      if (fstat(fd,&st) != 0) {
	fprintf(stderr,"fstat failed : %s\n",strerror(errno));
	return -1;
      }
      
      if (st.st_size > 0) {
	buf = map_file(fd,st.st_size);
	if (!buf) {
	  fprintf(stderr,"map_file failed : %s\n",strerror(errno));	  
	  return -1;
	}
      } else {
	buf = NULL;
      }

      if (verbose > 2)
	fprintf(stderr,"send_files mapped %s of size %d\n",
		fname,(int)st.st_size);

      write_int(f_out,i);

      write_int(f_out,s->count);
      write_int(f_out,s->n);
      write_int(f_out,s->remainder);

      if (verbose > 2)
	fprintf(stderr,"calling match_sums %s\n",fname);

      if (!am_server && verbose)
	printf("%s\n",fname);
      
      match_sums(f_out,s,buf,st.st_size);
      write_flush(f_out);
      
      unmap_file(buf,st.st_size);
      close(fd);

      free_sums(s);

      if (verbose > 2)
	fprintf(stderr,"sender finished %s\n",fname);

      total += st.st_size;
    }

  match_report();

  write_int(f_out,-1);
  write_flush(f_out);

  return total;
}