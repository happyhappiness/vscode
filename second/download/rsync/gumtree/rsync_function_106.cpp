void read_buf(int f,char *buf,int len)
{
  int ret;
  if ((ret=readfd(f,buf,len)) != len) {
    if (verbose > 1) 
      fprintf(stderr,"Error reading %d bytes : %s\n",
	      len,ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_read += len;
}