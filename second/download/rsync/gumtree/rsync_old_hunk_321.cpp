  n = read(f,read_buffer+read_buffer_len,n);
  if (n > 0) {
    read_buffer_len += n;
  }
}


static int readfd(int fd,char *buffer,int N)
{
  int  ret;
  int total=0;  

  if (read_buffer_len < N)
	  read_check(buffer_f_in);
 
  while (total < N)
    {
      if (read_buffer_len > 0 && buffer_f_in == fd) {
	ret = MIN(read_buffer_len,N-total);
	memcpy(buffer+total,read_buffer_p,ret);
	read_buffer_p += ret;
	read_buffer_len -= ret;
      } else {
	while ((ret = read(fd,buffer + total,N - total)) == -1) {
	  fd_set fds;

	  if (errno != EAGAIN && errno != EWOULDBLOCK)
	    return -1;
	  FD_ZERO(&fds);
	  FD_SET(fd, &fds);
	  select(fd+1, &fds, NULL, NULL, NULL);
	}
      }

      if (ret <= 0)
	return total;
      total += ret;
    }
  return total;
}


int read_int(int f)
{
  int ret;
