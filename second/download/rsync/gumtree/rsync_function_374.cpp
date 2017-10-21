static int receive_data(int f_in,struct map_struct *buf,int fd,char *fname)
{
  int i,n,remainder,len,count;
  off_t offset = 0;
  off_t offset2;
  char *data;
  static char file_sum1[MD4_SUM_LENGTH];
  static char file_sum2[MD4_SUM_LENGTH];
  char *map=NULL;

  count = read_int(f_in);
  n = read_int(f_in);
  remainder = read_int(f_in);

  sum_init();

  for (i=recv_token(f_in,&data); i != 0; i=recv_token(f_in,&data)) {
    if (i > 0) {
      if (verbose > 3)
	fprintf(FERROR,"data recv %d at %d\n",i,(int)offset);

      sum_update(data,i);

      if (fd != -1 && write_sparse(fd,data,i) != i) {
	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
	exit_cleanup(1);
      }
      offset += i;
    } else {
      i = -(i+1);
      offset2 = i*n;
      len = n;
      if (i == count-1 && remainder != 0)
	len = remainder;

      if (verbose > 3)
	fprintf(FERROR,"chunk[%d] of size %d at %d offset=%d\n",
		i,len,(int)offset2,(int)offset);

      map = map_ptr(buf,offset2,len);

      see_token(map, len);
      sum_update(map,len);

      if (fd != -1 && write_sparse(fd,map,len) != len) {
	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
	exit_cleanup(1);
      }
      offset += len;
    }
  }

  if (fd != -1 && offset > 0 && sparse_end(fd) != 0) {
    fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
    exit_cleanup(1);
  }

  sum_end(file_sum1);

  if (remote_version >= 14) {
    read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
    if (verbose > 2)
      fprintf(FERROR,"got file_sum\n");
    if (fd != -1 && memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0)
      return 0;
  }
  return 1;
}