  if (io_timeout)
	  last_io = time(NULL);

  return total;
}



void write_int(int f,int32 x)
{
  int ret;
  char b[4];
