	    ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_written += 4;
}

void write_buf(int f,char *buf,int len)
{
  int ret;
  if ((ret=writefd(f,buf,len)) != len) {
    fprintf(FERROR,"write_buf failed : %s\n",
	    ret==-1?strerror(errno):"EOF");
