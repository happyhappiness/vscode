int readfd(int fd,char *buffer,int N)
{
  int  ret;
  int total=0;  
 
  while (total < N)
    {
      ret = read(fd,buffer + total,N - total);

      if (ret <= 0)
	return total;
      total += ret;
    }
  return total;
}