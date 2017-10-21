 * have been read.  If all @p n can't be read then exit with an
 * error.
 **/
static void readfd(int fd, char *buffer, size_t N)
{
	int  ret;
	size_t total=0;  

	while (total < N) {
		ret = read_unbuffered(fd, buffer + total, N-total);
		total += ret;
	}

	stats.total_read += total;
}


int32 read_int(int f)
{
	char b[4];
	int32 ret;

	readfd(f,b,4);
	ret = IVAL(b,0);
	if (ret == (int32)0xffffffff) return -1;
	return ret;
}

int64 read_longint(int f)
{
	int64 ret;
	char b[8];
	ret = read_int(f);

	if ((int32)ret != (int32)0xffffffff) {
		return ret;
	}

#ifdef NO_INT64
	rprintf(FERROR,"Integer overflow - attempted 64 bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	readfd(f,b,8);
	ret = IVAL(b,0) | (((int64)IVAL(b,4))<<32);
#endif

	return ret;
}

void read_buf(int f,char *buf,size_t len)
{
	readfd(f,buf,len);
}

void read_sbuf(int f,char *buf,size_t len)
{
	read_buf(f,buf,len);
	buf[len] = 0;
}

unsigned char read_byte(int f)
{
	unsigned char c;
	read_buf(f, (char *)&c, 1);
	return c;
}


/**
 * Sleep after writing to limit I/O bandwidth usage.
 *
 * @todo Rather than sleeping after each write, it might be better to
 * use some kind of averaging.  The current algorithm seems to always
 * use a bit less bandwidth than specified, because it doesn't make up
 * for slow periods.  But arguably this is a feature.  In addition, we
 * ought to take the time used to write the data into account.
 **/
static void sleep_for_bwlimit(int bytes_written)
{
	struct timeval tv;

	if (!bwlimit)
		return;

	assert(bytes_written > 0);
	assert(bwlimit > 0);

	tv.tv_usec = bytes_written * 1000 / bwlimit;
	tv.tv_sec  = tv.tv_usec / 1000000;
	tv.tv_usec = tv.tv_usec % 1000000;

	select(0, NULL, NULL, NULL, &tv);
}


/**
 * Write len bytes to the file descriptor @p fd.
 *
 * This function underlies the multiplexing system.  The body of the
 * application never calls this function directly.
 **/
static void writefd_unbuffered(int fd,char *buf,size_t len)
{
	size_t total = 0;
	fd_set w_fds, r_fds;
	int fd_count, count;
	struct timeval tv;

	msg_list_push(NORMAL_FLUSH);

	no_flush++;

	while (total < len) {
		FD_ZERO(&w_fds);
		FD_SET(fd,&w_fds);
		fd_count = fd;

		if (msg_fd_in >= 0) {
			FD_ZERO(&r_fds);
			FD_SET(msg_fd_in,&r_fds);
			if (msg_fd_in > fd_count) 
				fd_count = msg_fd_in;
		}

		tv.tv_sec = io_timeout?io_timeout:SELECT_TIMEOUT;
		tv.tv_usec = 0;

		errno = 0;
		count = select(fd_count+1, msg_fd_in >= 0 ? &r_fds : NULL,
			       &w_fds, NULL, &tv);

		if (count == 0) {
			msg_list_push(NORMAL_FLUSH);
			check_timeout();
		}

		if (count <= 0) {
			if (errno == EBADF) {
				exit_cleanup(RERR_SOCKETIO);
			}
			continue;
		}

		if (msg_fd_in >= 0 && FD_ISSET(msg_fd_in, &r_fds))
			read_msg_fd();

		if (FD_ISSET(fd, &w_fds)) {
			int ret;
			size_t n = len-total;
			ret = write(fd,buf+total,n);

			if (ret < 0) {
				if (errno == EINTR)
					continue;
				if (errno == EWOULDBLOCK || errno == EAGAIN) {
					msleep(1);
					continue;
				}
			}

			if (ret <= 0) {
				/* Don't try to write errors back
				 * across the stream */
				io_multiplexing_close();
				rprintf(FERROR, RSYNC_NAME
					": writefd_unbuffered failed to write %ld bytes: phase \"%s\": %s\n",
					(long) len, io_write_phase, 
					strerror(errno));
				exit_cleanup(RERR_STREAMIO);
			}

			sleep_for_bwlimit(ret);
 
			total += ret;

			if (io_timeout)
				last_io = time(NULL);
		}
	}

	no_flush--;
}


static char *io_buffer;
static int io_buffer_count;

void io_start_buffering_out(int fd)
{
	if (io_buffer) return;
	multiplex_out_fd = fd;
	io_buffer = new_array(char, IO_BUFFER_SIZE);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;
}

void io_start_buffering_in(int fd)
{
	multiplex_in_fd = fd;
}

/**
 * Write an message to a multiplexed stream. If this fails then rsync
 * exits.
 **/
static void mplex_write(int fd, enum msgcode code, char *buf, size_t len)
{
	char buffer[4096];
	size_t n = len;

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	if (n > (sizeof buffer - 4)) {
		n = sizeof buffer - 4;
	}

	memcpy(&buffer[4], buf, n);
	writefd_unbuffered(fd, buffer, n+4);

	len -= n;
	buf += n;

	if (len) {
		writefd_unbuffered(fd, buf, len);
	}
}


void io_flush(int flush_it_all)
{
	int fd = multiplex_out_fd;
	
	msg_list_push(flush_it_all);

	if (!io_buffer_count || no_flush)
		return;

	if (io_multiplexing_out)
		mplex_write(fd, MSG_DATA, io_buffer, io_buffer_count);
	else
		writefd_unbuffered(fd, io_buffer, io_buffer_count);
	io_buffer_count = 0;
}


void io_end_buffering(void)
{
	io_flush(NORMAL_FLUSH);
	if (!io_multiplexing_out) {
		free(io_buffer);
		io_buffer = NULL;
	}
}

static void writefd(int fd,char *buf,size_t len)
{
	stats.total_written += len;

	msg_list_push(NORMAL_FLUSH);

	if (!io_buffer || fd != multiplex_out_fd) {
		writefd_unbuffered(fd, buf, len);
		return;
	}

	while (len) {
		int n = MIN((int) len, IO_BUFFER_SIZE-io_buffer_count);
		if (n > 0) {
			memcpy(io_buffer+io_buffer_count, buf, n);
			buf += n;
			len -= n;
			io_buffer_count += n;
		}

		if (io_buffer_count == IO_BUFFER_SIZE)
			io_flush(NORMAL_FLUSH);
	}
}


void write_int(int f,int32 x)
