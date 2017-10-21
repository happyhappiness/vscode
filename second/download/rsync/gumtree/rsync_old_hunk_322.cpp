    exit_cleanup(1);
  }
  total_read += 4;
  return IVAL(b,0);
}

void read_buf(int f,char *buf,int len)
{
  int ret;
  if ((ret=readfd(f,buf,len)) != len) {
    if (verbose > 1) 
      fprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
