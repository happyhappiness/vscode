static int readfd(int fd,char *buffer,int N)
{
  int  ret;
  int total=0;  
 
  while (total < N)
    {
      if (read_buffer_len > 0) {
	ret = MIN(read_buffer_len,N-total);
	memcpy(buffer+total,read_buffer_p,ret);
	read_buffer_p += ret;
	read_buffer_len -= ret;
      } else {
	ret = read(fd,buffer + total,N - total);
      }

      if (ret <= 0)
	return total;
      total += ret;
    }
  return total;
}