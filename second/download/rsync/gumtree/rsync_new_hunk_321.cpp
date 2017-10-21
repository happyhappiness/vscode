  n = read(f,read_buffer+read_buffer_len,n);
  if (n > 0) {
    read_buffer_len += n;
  }
}

static time_t last_io;


static void check_timeout(void)
{
	time_t t;
	
	if (!io_timeout) return;

	if (!last_io) {
		last_io = time(NULL);
		return;
	}

	t = time(NULL);

	if (last_io && io_timeout && (t-last_io)>io_timeout) {
		fprintf(FERROR,"read timeout after %d second - exiting\n", 
			(int)(t-last_io));
		exit_cleanup(1);
	}
}

static int readfd(int fd,char *buffer,int N)
{
	int  ret;
	int total=0;  
	struct timeval tv;
	
	if (read_buffer_len < N)
		read_check(buffer_f_in);
	
	while (total < N) {
		if (read_buffer_len > 0 && buffer_f_in == fd) {
			ret = MIN(read_buffer_len,N-total);
			memcpy(buffer+total,read_buffer_p,ret);
			read_buffer_p += ret;
			read_buffer_len -= ret;
			continue;
		} 

		while ((ret = read(fd,buffer + total,N-total)) == -1) {
			fd_set fds;

			if (errno != EAGAIN && errno != EWOULDBLOCK)
				return -1;
			FD_ZERO(&fds);
			FD_SET(fd, &fds);
			tv.tv_sec = io_timeout;
			tv.tv_usec = 0;

			if (select(fd+1, &fds, NULL, NULL, &tv) != 1) {
				check_timeout();
			}
		}

		if (ret <= 0)
			return total;
		total += ret;
	}

	if (io_timeout)
		last_io = time(NULL);
	return total;
}


int read_int(int f)
{
  int ret;
