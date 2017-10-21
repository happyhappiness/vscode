	return ret;
}


static int writefd_unbuffered(int fd,char *buf,int len)
{
	int total = 0;
	fd_set w_fds, r_fds;
	int fd_count, count, got_select=0;
	struct timeval tv;

	while (total < len) {
		int ret = write(fd,buf+total,len-total);

		if (ret == 0) return total;

		if (ret == -1 && !(errno == EWOULDBLOCK || errno == EAGAIN)) 
			return -1;

		if (ret == -1 && got_select) {
			/* hmmm, we got a write select on the fd and
			   then failed to write.  Why doesn't that
			   mean that the fd is dead? It doesn't on
			   some systems it seems (eg. IRIX) */
			u_sleep(1000);
		}

		got_select = 0;


		if (ret != -1) {
			total += ret;
			continue;
		}

		if (read_buffer_len < MAX_READ_BUFFER && buffer_f_in != -1)
			read_check(buffer_f_in);

		fd_count = fd+1;
		FD_ZERO(&w_fds);
		FD_ZERO(&r_fds);
		FD_SET(fd,&w_fds);
		if (buffer_f_in != -1) {
			FD_SET(buffer_f_in,&r_fds);
			if (buffer_f_in > fd) 
				fd_count = buffer_f_in+1;
		}

		tv.tv_sec = BLOCKING_TIMEOUT;
		tv.tv_usec = 0;
		count = select(fd_count,buffer_f_in == -1? NULL: &r_fds,
			       &w_fds,NULL,&tv);
		
		if (count == -1 && errno != EINTR) {
			if (verbose > 1) 
				rprintf(FERROR,"select error: %s\n", strerror(errno));
			exit_cleanup(1);
		}
		
		if (count == 0) {
			check_timeout();
			continue;
		}
		
		if (FD_ISSET(fd, &w_fds)) {
			got_select = 1;
		}
	}

	if (io_timeout)
		last_io = time(NULL);
	
	return total;
}


static char *io_buffer;
static int io_buffer_count;

void io_start_buffering(int fd)
{
	if (io_buffer) return;
	multiplex_out_fd = fd;
	io_buffer = (char *)malloc(IO_BUFFER_SIZE+4);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;

	/* leave room for the multiplex header in case it's needed */
	io_buffer += 4;
}

void io_flush(void)
{
	int fd = multiplex_out_fd;
	if (!io_buffer_count) return;

	if (io_multiplexing_out) {
		SIVAL(io_buffer-4, 0, (MPLEX_BASE<<24) + io_buffer_count);
		if (writefd_unbuffered(fd, io_buffer-4, io_buffer_count+4) !=
		    io_buffer_count+4) {
			rprintf(FERROR,"write failed\n");
			exit_cleanup(1);
		}
	} else {
		if (writefd_unbuffered(fd, io_buffer, io_buffer_count) != 
		    io_buffer_count) {
			rprintf(FERROR,"write failed\n");
			exit_cleanup(1);
		}
	}
	io_buffer_count = 0;
}

void io_end_buffering(int fd)
{
	io_flush();
	if (!io_multiplexing_out) {
		free(io_buffer-4);
		io_buffer = NULL;
	}
}

static int writefd(int fd,char *buf,int len1)
{
	int len = len1;

