  int ret;
  char b[4];
  SIVAL(b,0,x);
  if ((ret=writefd(f,b,4)) != 4) {
    fprintf(stderr,"write_int failed : %s\n",
	    ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_written += 4;
}

void write_buf(int f,char *buf,int len)
{
  int ret;
  if ((ret=writefd(f,buf,len)) != len) {
    fprintf(stderr,"write_buf failed : %s\n",
	    ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_written += len;
}


void write_byte(int f,unsigned char c)
