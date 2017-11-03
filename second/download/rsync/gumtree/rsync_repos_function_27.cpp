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