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
			total += ret;
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

			if (select(fd+1, &fds, NULL, NULL, 
				   io_timeout?&tv:NULL) != 1) {
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