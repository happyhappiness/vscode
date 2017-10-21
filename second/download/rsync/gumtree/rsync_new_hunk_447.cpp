	  struct file_struct *file = flist->files[i];
	  if (!file->basename || !S_ISDIR(file->mode)) continue;
	  recv_generator(f_name(file),flist,i,-1);
  }

  if (verbose > 2)
    rprintf(FINFO,"recv_files finished\n");
  
  return 0;
}



void send_files(struct file_list *flist,int f_out,int f_in)
{ 
  int fd;
  struct sum_struct *s;
  struct map_struct *buf;
  STRUCT_STAT st;
  char fname[MAXPATHLEN];  
  int i;
  struct file_struct *file;
  int phase = 0;
  int offset=0;

  if (verbose > 2)
    rprintf(FINFO,"send_files starting\n");

  setup_nonblocking(f_in,f_out);

  while (1) {
	  i = read_int(f_in);
	  if (i == -1) {
		  if (phase==0 && remote_version >= 13) {
			  phase++;
			  csum_length = SUM_LENGTH;
			  write_int(f_out,-1);
			  write_flush(f_out);
			  if (verbose > 2)
				  rprintf(FINFO,"send_files phase=%d\n",phase);
			  continue;
		  }
		  break;
	  }

	  file = flist->files[i];

	  fname[0] = 0;
	  if (file->basedir) {
		  strlcpy(fname,file->basedir,MAXPATHLEN-1);
		  if (strlen(fname) == MAXPATHLEN-1) {
			  io_error = 1;
			  rprintf(FERROR, "send_files failed on long-named directory %s\n",
				  fname);
			  return;
		  }
		  strcat(fname,"/");
		  offset = strlen(file->basedir)+1;
	  }
	  strncat(fname,f_name(file),MAXPATHLEN-strlen(fname));
	  
	  if (verbose > 2) 
		  rprintf(FINFO,"send_files(%d,%s)\n",i,fname);
	  
	  if (dry_run) {	
		  if (!am_server && verbose)
			  printf("%s\n",fname);
		  write_int(f_out,i);
		  continue;
	  }

	  s = receive_sums(f_in);
	  if (!s) {
		  io_error = 1;
		  rprintf(FERROR,"receive_sums failed\n");
		  return;
	  }
	  
	  fd = open(fname,O_RDONLY);
	  if (fd == -1) {
		  io_error = 1;
		  rprintf(FERROR,"send_files failed to open %s: %s\n",
			  fname,strerror(errno));
		  free_sums(s);
		  continue;
	  }
	  
	  /* map the local file */
	  if (do_fstat(fd,&st) != 0) {
		  io_error = 1;
		  rprintf(FERROR,"fstat failed : %s\n",strerror(errno));
		  free_sums(s);
		  close(fd);
		  return;
	  }
	  
	  if (st.st_size > 0) {
		  buf = map_file(fd,st.st_size);
	  } else {
		  buf = NULL;
	  }
	  
	  if (verbose > 2)
		  rprintf(FINFO,"send_files mapped %s of size %d\n",
			  fname,(int)st.st_size);
	  
	  write_int(f_out,i);
	  
	  write_int(f_out,s->count);
	  write_int(f_out,s->n);
	  write_int(f_out,s->remainder);
	  
	  if (verbose > 2)
		  rprintf(FINFO,"calling match_sums %s\n",fname);
	  
	  if (!am_server && verbose)
		  printf("%s\n",fname+offset);
	  
	  match_sums(f_out,s,buf,st.st_size);
	  write_flush(f_out);
