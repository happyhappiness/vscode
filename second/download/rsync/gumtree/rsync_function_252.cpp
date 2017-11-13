int read_int(int f)
{
  char b[4];
  if (readfd(f,b,4) != 4) {
    if (verbose > 1) 
      fprintf(stderr,"Error reading %d bytes : %s\n",4,strerror(errno));
    exit(1);
  }
  total_read += 4;
  return IVAL(b,0);
}