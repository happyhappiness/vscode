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