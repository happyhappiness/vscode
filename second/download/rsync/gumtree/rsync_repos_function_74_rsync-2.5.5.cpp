static void writefd_unbuffered(int fd,char *buf,size_t len)
{
	size_t total = 0;
	fd_set w_fds, r_fds;
	int fd_count, count;
	struct timeval tv;

	err_list_push();

	no_flush++;

	while (total < len) {
		FD_ZERO(&w_fds);
		FD_ZERO(&r_fds);
		FD_SET(fd,&w_fds);
		fd_count = fd;

		if (io_error_fd != -1) {
			FD_SET(io_error_fd,&r_fds);
			if (io_error_fd > fd_count) 
				fd_count = io_error_fd;
		}

		tv.tv_sec = io_timeout?io_timeout:SELECT_TIMEOUT;
		tv.tv_usec = 0;

		errno = 0;

		count = select(fd_count+1,
			       io_error_fd != -1?&r_fds:NULL,
			       &w_fds,NULL,
			       &tv);

		if (count == 0) {
			check_timeout();
		}

		if (count <= 0) {
			if (errno == EBADF) {
				exit_cleanup(RERR_SOCKETIO);
			}
			continue;
		}

		if (io_error_fd != -1 && FD_ISSET(io_error_fd, &r_fds)) {
			read_error_fd();
		}

		if (FD_ISSET(fd, &w_fds)) {
			int ret;
			size_t n = len-total;
			ret = write(fd,buf+total,n);

			if (ret == -1 && errno == EINTR) {
				continue;
			}

			if (ret == -1 && 
			    (errno == EWOULDBLOCK || errno == EAGAIN)) {
				msleep(1);
				continue;
			}

			if (ret <= 0) {
				/* Don't try to write errors back
				 * across the stream */
				io_multiplexing_close();
				rprintf(FERROR, RSYNC_NAME
					": error writing %d unbuffered bytes"
					" - exiting: %s\n", len,
					strerror(errno));
				exit_cleanup(RERR_STREAMIO);
			}

			/* Sleep after writing to limit I/O bandwidth */
			if (bwlimit)
			{
			    tv.tv_sec = 0;
			    tv.tv_usec = ret * 1000 / bwlimit;
			    while (tv.tv_usec > 1000000)
			    {
				tv.tv_sec++;
				tv.tv_usec -= 1000000;
			    }
			    select(0, NULL, NULL, NULL, &tv);
 			}
 
			total += ret;

			if (io_timeout)
				last_io = time(NULL);
		}
	}

	no_flush--;
}