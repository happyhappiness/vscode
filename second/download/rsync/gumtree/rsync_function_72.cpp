static void receive_data(int f_in,char *buf,int fd)
{
  int i,n,remainder,len,count;
  int size = 0;
  char *buf2=NULL;
  off_t offset = 0;
  off_t offset2;

  count = read_int(f_in);
  n = read_int(f_in);
  remainder = read_int(f_in);

  for (i=read_int(f_in); i != 0; i=read_int(f_in)) {
    if (i > 0) {
      if (i > size) {
	if (buf2) free(buf2);
	buf2 = (char *)malloc(i);
	size = i;
	if (!buf2) out_of_memory("receive_data");
      }

      if (verbose > 3)
	fprintf(stderr,"data recv %d at %d\n",i,(int)offset);

      read_buf(f_in,buf2,i);
      write(fd,buf2,i);
      offset += i;
    } else {
      i = -(i+1);
      offset2 = i*n;
      len = n;
      if (i == count-1 && remainder != 0)
	len = remainder;

      if (verbose > 3)
	fprintf(stderr,"chunk[%d] of size %d at %d offset=%d\n",
		i,len,(int)offset2,(int)offset);

      write(fd,buf+offset2,len);
      offset += len;
    }
  }
  if (buf2) free(buf2);
}