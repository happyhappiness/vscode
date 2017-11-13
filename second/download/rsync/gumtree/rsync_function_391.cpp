off_t send_files(struct file_list *flist,int f_out,int f_in)
{ 
  int fd;
  struct sum_struct *s;
  struct map_struct *buf;
  struct stat st;
  char fname[MAXPATHLEN];  
  off_t total=0;
  int i;
  struct file_struct *file;
  int phase = 0;

  if (verbose > 2)
    fprintf(FERROR,"send_files starting\n");

  setup_nonblocking(f_in,f_out);

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) {
	if (phase==0 && remote_version >= 13) {
	  phase++;
	  csum_length = SUM_LENGTH;
	  write_int(f_out,-1);
	  write_flush(f_out);
	  if (verbose > 2)
	    fprintf(FERROR,"send_files phase=%d\n",phase);
	  continue;
	}
	break;
      }

      file = &flist->files[i];

      fname[0] = 0;
      if (file->dir) {
	strncpy(fname,file->dir,MAXPATHLEN-1);
	fname[MAXPATHLEN-1] = 0;
      if (strlen(fname) == MAXPATHLEN-1) {
        fprintf(FERROR, "send_files failed on long-named directory %s\n",
                fname);
        return -1;
      }
	strcat(fname,"/");
      }
      strncat(fname,file->name,MAXPATHLEN-strlen(fname));

      if (verbose > 2) 
	fprintf(FERROR,"send_files(%d,%s)\n",i,fname);

      if (dry_run) {	
	if (!am_server && verbose)
	  printf("%s\n",fname);
	write_int(f_out,i);
	continue;
      }

      s = receive_sums(f_in);
      if (!s) {
	fprintf(FERROR,"receive_sums failed\n");
	return -1;
      }

      fd = open(fname,O_RDONLY);
      if (fd == -1) {
	fprintf(FERROR,"send_files failed to open %s: %s\n",
		fname,strerror(errno));
	continue;
      }
  
      /* map the local file */
      if (fstat(fd,&st) != 0) {
	fprintf(FERROR,"fstat failed : %s\n",strerror(errno));
	close(fd);
	return -1;
      }
      
      if (st.st_size > 0) {
	buf = map_file(fd,st.st_size);
      } else {
	buf = NULL;
      }

      if (verbose > 2)
	fprintf(FERROR,"send_files mapped %s of size %d\n",
		fname,(int)st.st_size);

      write_int(f_out,i);

      write_int(f_out,s->count);
      write_int(f_out,s->n);
      write_int(f_out,s->remainder);

      if (verbose > 2)
	fprintf(FERROR,"calling match_sums %s\n",fname);

      if (!am_server && verbose)
	printf("%s\n",fname);
      
      match_sums(f_out,s,buf,st.st_size);
      write_flush(f_out);
      
      if (buf) unmap_file(buf);
      close(fd);

      free_sums(s);

      if (verbose > 2)
	fprintf(FERROR,"sender finished %s\n",fname);

      total += st.st_size;
    }

  if (verbose > 2)
    fprintf(FERROR,"send files finished\n");

  match_report();

  write_int(f_out,-1);
  write_flush(f_out);

  return total;
}