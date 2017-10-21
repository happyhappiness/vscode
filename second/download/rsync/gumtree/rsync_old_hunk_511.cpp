
/* This function was added to overcome a deadlock problem when using
 * ssh.  It looks like we can't allow our receive queue to get full or
 * ssh will clag up. Uggh.  */
static void read_check(int f)
{
  int n;

  if (f == -1) return;

  if (read_buffer_len == 0) {
    read_buffer_p = read_buffer;
  }

  if ((n=num_waiting(f)) <= 0)
    return;

  /* things could deteriorate if we read in really small chunks */
  if (n < 10) n = 1024;

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

static time_t last_io;


static void check_timeout(void)
