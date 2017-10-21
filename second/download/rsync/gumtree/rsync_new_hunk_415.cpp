
  return total;
}



void write_int(int f,int32 x)
{
  int ret;
  char b[4];
  SIVAL(b,0,x);
  if ((ret=writefd(f,b,4)) != 4) {
    rprintf(FERROR,"write_int failed : %s\n",
	    ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_written += 4;
}

