int read_int(int f)
{
  int ret;
  char b[4];
  if ((ret=readfd(f,b,4)) != 4) {
    if (verbose > 1) 
      fprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
	      getpid(),4,ret==-1?strerror(errno):"EOF");
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
	      getpid(),len,ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_read += len;
}

unsigned char read_byte(int f)
{
  unsigned char c;
  read_buf(f,(char *)&c,1);
  return c;
}


static char last_byte=0;
static int last_sparse = 0;

