void write_buf(int f,char *buf,int len)
{
  if (write(f,buf,len) != len) {
    fprintf(stderr,"write_buf failed : %s\n",strerror(errno));
    exit(1);
  }
  total_written += len;
}