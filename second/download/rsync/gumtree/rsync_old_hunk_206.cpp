}



void write_int(int f,int x)
{
  char b[4];
  SIVAL(b,0,x);
  if (writefd(f,b,4) != 4) {
    fprintf(stderr,"write_int failed : %s\n",strerror(errno));
    exit(1);
  }
  total_written += 4;
}

void write_buf(int f,char *buf,int len)
{
  if (writefd(f,buf,len) != len) {
    fprintf(stderr,"write_buf failed : %s\n",strerror(errno));
    exit(1);
  }
  total_written += len;
}


