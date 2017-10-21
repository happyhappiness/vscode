 * have been read.  If all @p n can't be read then exit with an
 * error.
 **/
static void readfd(int fd, char *buffer, size_t N)
{
	int  ret;
	size_t total = 0;

	while (total < N) {
		ret = readfd_unbuffered(fd, buffer + total, N-total);
		total += ret;
	}

	if (fd == write_batch_monitor_in) {
		if ((size_t)write(batch_fd, buffer, total) != total)
			exit_cleanup(RERR_FILEIO);
	}

	if (fd == sock_f_in)
		stats.total_read += total;
}


int32 read_int(int f)
{
	char b[4];
	int32 ret;

	readfd(f,b,4);
	ret = IVAL(b,0);
	if (ret == (int32)0xffffffff)
		return -1;
	return ret;
}

int64 read_longint(int f)
{
	int64 ret;
	char b[8];
	ret = read_int(f);

	if ((int32)ret != (int32)0xffffffff)
		return ret;

#ifdef INT64_IS_OFF_T
	if (sizeof (int64) < 8) {
		rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
		exit_cleanup(RERR_UNSUPPORTED);
	}
#endif
	readfd(f,b,8);
	ret = IVAL(b,0) | (((int64)IVAL(b,4))<<32);

	return ret;
}

void read_buf(int f,char *buf,size_t len)
{
	readfd(f,buf,len);
}

void read_sbuf(int f,char *buf,size_t len)
{
	readfd(f, buf, len);
	buf[len] = 0;
}

unsigned char read_byte(int f)
{
	unsigned char c;
	readfd(f, (char *)&c, 1);
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
 *
 * During some phases of big transfers (file FOO is uptodate) this is
 * called with a small bytes_written every time.  As the kernel has to
 * round small waits up to guarantee that we actually wait at least the
 * requested number of microseconds, this can become grossly inaccurate.
 * We therefore keep track of the bytes we've written over time and only
 * sleep when the accumulated delay is at least 1 tenth of a second.
 **/
static void sleep_for_bwlimit(int bytes_written)
{
	static struct timeval prior_tv;
	static long total_written = 0; 
	struct timeval tv, start_tv;
	long elapsed_usec, sleep_usec;

#define ONE_SEC	1000000L /* # of microseconds in a second */

	if (!bwlimit)
		return;

	total_written += bytes_written; 

	gettimeofday(&start_tv, NULL);
	if (prior_tv.tv_sec) {
		elapsed_usec = (start_tv.tv_sec - prior_tv.tv_sec) * ONE_SEC
			     + (start_tv.tv_usec - prior_tv.tv_usec);
		total_written -= elapsed_usec * bwlimit / (ONE_SEC/1024);
		if (total_written < 0)
			total_written = 0;
	}

	sleep_usec = total_written * (ONE_SEC/1024) / bwlimit;
	if (sleep_usec < ONE_SEC / 10) {
		prior_tv = start_tv;
		return;
	}

	tv.tv_sec  = sleep_usec / ONE_SEC;
	tv.tv_usec = sleep_usec % ONE_SEC;
	select(0, NULL, NULL, NULL, &tv);

	gettimeofday(&prior_tv, NULL);
	elapsed_usec = (prior_tv.tv_sec - start_tv.tv_sec) * ONE_SEC
		     + (prior_tv.tv_usec - start_tv.tv_usec);
	total_written = (sleep_usec - elapsed_usec) * bwlimit / (ONE_SEC/1024);
}


/* Write len bytes to the file descriptor fd, looping as necessary to get
 * the job done and also (in the generator) reading any data on msg_fd_in
 * (to avoid deadlock).
 *
 * This function underlies the multiplexing system.  The body of the
 * application never calls this function directly. */
static void writefd_unbuffered(int fd,char *buf,size_t len)
{
	size_t n, total = 0;
	fd_set w_fds, r_fds;
	int maxfd, count, ret;
	struct timeval tv;

	no_flush++;

	while (total < len) {
		FD_ZERO(&w_fds);
		FD_SET(fd,&w_fds);
		maxfd = fd;

		if (msg_fd_in >= 0) {
			FD_ZERO(&r_fds);
			FD_SET(msg_fd_in,&r_fds);
			if (msg_fd_in > maxfd)
				maxfd = msg_fd_in;
		}

		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		errno = 0;
		count = select(maxfd + 1, msg_fd_in >= 0 ? &r_fds : NULL,
			       &w_fds, NULL, &tv);

		if (count <= 0) {
			if (count < 0 && errno == EBADF)
				exit_cleanup(RERR_SOCKETIO);
			check_timeout();
			continue;
		}

		if (msg_fd_in >= 0 && FD_ISSET(msg_fd_in, &r_fds))
			read_msg_fd();

		if (!FD_ISSET(fd, &w_fds))
			continue;

		n = len - total;
		if (bwlimit && n > bwlimit_writemax)
			n = bwlimit_writemax;
		ret = write(fd, buf + total, n);

		if (ret <= 0) {
			if (ret < 0) {
				if (errno == EINTR)
					continue;
				if (errno == EWOULDBLOCK || errno == EAGAIN) {
					msleep(1);
					continue;
				}
			}

			/* Don't try to write errors back across the stream. */
			if (fd == sock_f_out)
				close_multiplexing_out();
			rsyserr(FERROR, errno,
				"writefd_unbuffered failed to write %ld bytes: phase \"%s\" [%s]",
				(long)len, io_write_phase, who_am_i());
			/* If the other side is sending us error messages, try
			 * to grab any messages they sent before they died. */
			while (fd == sock_f_out && io_multiplexing_in) {
				io_timeout = 30;
				readfd_unbuffered(sock_f_in, io_filesfrom_buf,
						  sizeof io_filesfrom_buf);
			}
			exit_cleanup(RERR_STREAMIO);
		}

		total += ret;

		if (fd == sock_f_out) {
			if (io_timeout)
				last_io = time(NULL);
			sleep_for_bwlimit(ret);
		}
	}

	no_flush--;
}


/**
 * Write an message to a multiplexed stream. If this fails then rsync
 * exits.
 **/
static void mplex_write(enum msgcode code, char *buf, size_t len)
{
	char buffer[4096];
	size_t n = len;

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	if (n > sizeof buffer - 4)
		n = sizeof buffer - 4;

	memcpy(&buffer[4], buf, n);
	writefd_unbuffered(sock_f_out, buffer, n+4);

	len -= n;
	buf += n;

	if (len)
		writefd_unbuffered(sock_f_out, buf, len);
}


void io_flush(int flush_it_all)
{
	msg_list_push(flush_it_all);

	if (!iobuf_out_cnt || no_flush)
		return;

	if (io_multiplexing_out)
		mplex_write(MSG_DATA, iobuf_out, iobuf_out_cnt);
	else
		writefd_unbuffered(sock_f_out, iobuf_out, iobuf_out_cnt);
	iobuf_out_cnt = 0;
}


static void writefd(int fd,char *buf,size_t len)
{
	if (fd == msg_fd_out) {
		rprintf(FERROR, "Internal error: wrong write used in receiver.\n");
		exit_cleanup(RERR_PROTOCOL);
	}

	if (fd == sock_f_out)
		stats.total_written += len;

	if (fd == write_batch_monitor_out) {
		if ((size_t)write(batch_fd, buf, len) != len)
			exit_cleanup(RERR_FILEIO);
	}

	if (!iobuf_out || fd != sock_f_out) {
		writefd_unbuffered(fd, buf, len);
		return;
	}

	while (len) {
		int n = MIN((int)len, IO_BUFFER_SIZE - iobuf_out_cnt);
		if (n > 0) {
			memcpy(iobuf_out+iobuf_out_cnt, buf, n);
			buf += n;
			len -= n;
			iobuf_out_cnt += n;
		}

		if (iobuf_out_cnt == IO_BUFFER_SIZE)
			io_flush(NORMAL_FLUSH);
	}
}


void write_int(int f,int32 x)
