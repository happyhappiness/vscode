void write_int(int f,int x)
{
  char b[4];
  SIVAL(b,0,x);
  if (write(f,b,4) != 4) {
    fprintf(stderr,"write_int failed : %s\n",strerror(errno));
    exit(1);
  }
  total_written += 4;
}