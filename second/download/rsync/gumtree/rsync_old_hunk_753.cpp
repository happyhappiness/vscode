
	if (x <= 0x7FFFFFFF) {
		write_int(f, (int)x);
		return;
	}

#ifdef NO_INT64
	rprintf(FERROR,"Integer overflow - attempted 64 bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	write_int(f, (int32)0xFFFFFFFF);
	SIVAL(b,0,(x&0xFFFFFFFF));
	SIVAL(b,4,((x>>32)&0xFFFFFFFF));

	writefd(f,b,8);
#endif
}

void write_buf(int f,char *buf,size_t len)
{
	writefd(f,buf,len);
}

/** Write a string to the connection */
static void write_sbuf(int f,char *buf)
{
	write_buf(f, buf, strlen(buf));
}


void write_byte(int f,unsigned char c)
{
	write_buf(f,(char *)&c,1);
}



/**
 * Read a line of up to @p maxlen characters into @p buf.  Does not
 * contain a trailing newline or carriage return.
 *
 * @return 1 for success; 0 for io error or truncation.
 **/
int read_line(int f, char *buf, size_t maxlen)
{
	while (maxlen) {
		buf[0] = 0;
		read_buf(f, buf, 1);
		if (buf[0] == 0)
			return 0;
		if (buf[0] == '\n') {
			buf[0] = 0;
			break;
		}
		if (buf[0] != '\r') {
			buf++;
			maxlen--;
		}
	}
	if (maxlen == 0) {
		*buf = 0;
		return 0;
	}

	return 1;
}


void io_printf(int fd, const char *format, ...)
{
	va_list ap;  
	char buf[1024];
	int len;

	va_start(ap, format);
	len = vsnprintf(buf, sizeof buf, format, ap);
	va_end(ap);

	if (len < 0) exit_cleanup(RERR_STREAMIO);

	write_sbuf(fd, buf);
}


/** Setup for multiplexing a MSG_* stream with the data stream. */
void io_start_multiplex_out(int fd)
{
	multiplex_out_fd = fd;
	io_flush(NORMAL_FLUSH);
	io_start_buffering_out(fd);
	io_multiplexing_out = 1;
}

/** Setup for multiplexing a MSG_* stream with the data stream. */
void io_start_multiplex_in(int fd)
{
	multiplex_in_fd = fd;
	io_flush(NORMAL_FLUSH);
	io_multiplexing_in = 1;
}

/** Write an message to the multiplexed data stream. */
int io_multiplex_write(enum msgcode code, char *buf, size_t len)
{
	if (!io_multiplexing_out) return 0;

	io_flush(NORMAL_FLUSH);
	stats.total_written += (len+4);
	mplex_write(multiplex_out_fd, code, buf, len);
	return 1;
}

/** Stop output multiplexing. */
void io_multiplexing_close(void)
{
	io_multiplexing_out = 0;
}

