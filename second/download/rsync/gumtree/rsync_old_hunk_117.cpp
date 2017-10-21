  return (l + write(f,buf+l,len-l));
}

int read_write(int fd_in,int fd_out,int size)
{
  static char *buf=NULL;
  static int bufsize = WRITE_BLOCK_SIZE;
  int total=0;
  
  if (!buf) {
    buf = (char *)malloc(bufsize);
    if (!buf) out_of_memory("read_write");
  }
