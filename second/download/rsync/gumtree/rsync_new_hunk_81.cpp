    fprintf(stderr,"write_buf failed : %s\n",strerror(errno));
    exit(1);
  }
  total_written += len;
}

static int num_waiting(int fd)
{
  int len=0;
#ifdef FIONREAD
  ioctl(fd,FIONREAD,&len);
#endif
  return(len);
}

static char *read_buffer = NULL;
static char *read_buffer_p = NULL;
static int read_buffer_len = 0;
static int read_buffer_size = 0;


void write_flush(int f)
{
}


/* This function was added to overcome a deadlock problem when using
 * ssh.  It looks like we can't allow our receive queue to get full or
 * ssh will clag up. Uggh.  */
void read_check(int f)
{
  int n;

  if (read_buffer_len == 0) {
    read_buffer_p = read_buffer;
  }

  if ((n=num_waiting(f)) <= 0)
    return;

  if (read_buffer_p != read_buffer) {
    memmove(read_buffer,read_buffer_p,read_buffer_len);
    read_buffer_p = read_buffer;
  }

  if (n > (read_buffer_size - read_buffer_len)) {
    read_buffer_size += n;
    if (!read_buffer)
      read_buffer = (char *)malloc(read_buffer_size);
    else
      read_buffer = (char *)realloc(read_buffer,read_buffer_size);
    if (!read_buffer) out_of_memory("read check");      
    read_buffer_p = read_buffer;      
  }

  n = read(f,read_buffer+read_buffer_len,n);
  if (n > 0) {
    read_buffer_len += n;
  }
}


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
