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

  close(fd);
  unmap_file(buf,st.st_size);

  free_sums(s);
}



static void receive_data(int f_in,char *buf,int fd,char *fname)
{
  int i,n,remainder,len,count;
  off_t offset = 0;
  off_t offset2;

  count = read_int(f_in);
  n = read_int(f_in);
  remainder = read_int(f_in);

  for (i=read_int(f_in); i != 0; i=read_int(f_in)) {
    if (i > 0) {
      if (verbose > 3)
	fprintf(FERROR,"data recv %d at %d\n",i,(int)offset);

      if (read_write(f_in,fd,i) != i) {
	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
	exit_cleanup(1);
      }
      offset += i;
    } else {
      i = -(i+1);
