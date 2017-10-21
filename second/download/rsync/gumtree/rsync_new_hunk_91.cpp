      fprintf(stderr,"Error reading %d bytes : %s\n",len,strerror(errno));
    exit(1);
  }
  total_read += len;
}

unsigned char read_byte(int f)
{
  char c;
  read_buf(f,&c,1);
  return (unsigned char)c;
}

int read_write(int fd_in,int fd_out,int size)
{
  static char *buf=NULL;
  static int bufsize = WRITE_BLOCK_SIZE;
  int total=0;
