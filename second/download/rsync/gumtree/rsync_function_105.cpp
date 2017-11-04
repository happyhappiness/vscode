int read_int(int f)
{
  int ret;
  char b[4];
  if ((ret=readfd(f,b,4)) != 4) {
    if (verbose > 1) 
      fprintf(stderr,"Error reading %d bytes : %s\n",
	      4,ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_read += 4;
  return IVAL(b,0);
}