static void writefd_unbuffered(int fd,char *buf,int len)
{
	int total = 0;
	fd_set w_fds, r_fds;
	int fd_count, count;
	struct timeval tv;
	int reading;

	no_flush++;

	reading = (buffer_f_in != -1 && read_buffer_len < MAX_READ_BUFFER);

	while (total < len) {
		FD_ZERO(&w_fds);
		FD_ZERO(&r_fds);
		FD_SET(fd,&w_fds);
		fd_count = fd+1;

		if (reading) {
			FD_SET(buffer_f_in,&r_fds);
			if (buffer_f_in > fd) 
				fd_count = buffer_f_in+1;
		}

		tv.tv_sec = io_timeout;
		tv.tv_usec = 0;

		count = select(fd_count,
			       reading?&r_fds:NULL,
			       &w_fds,NULL,
			       io_timeout?&tv:NULL);

		if (count <= 0) {
			check_timeout();
			continue;
		}

		if (FD_ISSET(fd, &w_fds)) {
			int ret = write(fd,buf+total,len-total);

			if (ret == -1 && errno == EINTR) {
				continue;
			}

			if (ret == -1 && 
			    (errno == EAGAIN || errno == EWOULDBLOCK)) {
				/* this shouldn't happen, if it does then
				   sleep for a short time to prevent us
				   chewing too much CPU */
				u_sleep(100);
				continue;
			}

			if (ret <= 0) {
				rprintf(FERROR,"erroring writing %d bytes - exiting\n", len);
				exit_cleanup(1);
			}

			total += ret;
			stats.total_written += ret;

			if (io_timeout)
				last_io = time(NULL);
			continue;
		}

		if (reading && FD_ISSET(buffer_f_in, &r_fds)) {
			read_check(buffer_f_in);
		}
	}

	no_flush--;
}