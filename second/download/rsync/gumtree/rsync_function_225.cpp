void read_buf(int f,char *buf,int len)
{
  if (readfd(f,buf,len) != len) {
    if (verbose > 1) 
      fprintf(stderr,"Error reading %d bytes : %s\n",len,strerror(errno));
    exit(1);
  }
  total_read += len;
}