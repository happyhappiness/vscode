
static char last_byte=0;
static int last_sparse = 0;

int sparse_end(int f)
{
  if (last_sparse) {
    lseek(f,-1,SEEK_CUR);
    return (write(f,&last_byte,1) == 1 ? 0 : -1);
  }
  last_sparse = 0;
  return 0;
}

int write_sparse(int f,char *buf,int len)
{
  int l1=0,l2=0;
  int ret;

  if (!sparse_files) 
    return write(f,buf,len);

  for (l1=0;l1<len && buf[l1]==0;l1++) ;
  for (l2=0;l2<(len-l1) && buf[len-(l2+1)]==0;l2++) ;

  last_byte = buf[len-1];

  if (l1 == len || l2 > 0)
    last_sparse=1;

  if (l1 > 0)
    lseek(f,l1,SEEK_CUR);  

  if (l1 == len) 
    return len;

  if ((ret=write(f,buf+l1,len-(l1+l2))) != len-(l1+l2)) {
    if (ret == -1 || ret == 0) return ret;
    return (l1+ret);
  }

  if (l2 > 0)
    lseek(f,l2,SEEK_CUR);

  return len;
}

int read_write(int fd_in,int fd_out,int size)
{
  static char *buf=NULL;
  int bufsize = sparse_files?SPARSE_WRITE_SIZE:WRITE_SIZE;
  int total=0;
  
  if (!buf) {
    buf = (char *)malloc(bufsize);
    if (!buf) out_of_memory("read_write");
  }
