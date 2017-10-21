
static char last_byte=0;
static int last_sparse = 0;

int sparse_end(int f)
{
#if SPARSE_FILES
  if (last_sparse) {
    lseek(f,-1,SEEK_CUR);
    return (write(f,&last_byte,1) == 1 ? 0 : -1);
  }
#endif  
  last_sparse = 0;
  return 0;
}

int write_sparse(int f,char *buf,int len)
{
  int l=0;

#if SPARSE_FILES
  for (l=0;l<len && buf[l]==0;l++) ;

  if (l > 0)
    lseek(f,l,SEEK_CUR);

  last_byte = buf[len-1];
#endif

  if (l == len) {
    last_sparse = 1;
    return len;
  } 

  last_sparse = 0;

  return (l + write(f,buf+l,len-l));
}

int read_write(int fd_in,int fd_out,int size)
{
  static char *buf=NULL;
  static int bufsize = CHUNK_SIZE;
  int total=0;
  
  if (!buf) {
    buf = (char *)malloc(bufsize);
    if (!buf) out_of_memory("read_write");
  }
