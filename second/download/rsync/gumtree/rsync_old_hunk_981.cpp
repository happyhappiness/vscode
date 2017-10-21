	glob_expand(NULL, NULL, NULL, NULL);

	*argc_p = argc;
	*argv_p = argv;
}

int io_start_buffering_out(int f_out)
{
	if (iobuf_out) {
		assert(f_out == iobuf_f_out);
		return 0;
	}
	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
		out_of_memory("io_start_buffering_out");
	iobuf_out_cnt = 0;
	iobuf_f_out = f_out;
	return 1;
}

int io_start_buffering_in(int f_in)
{
	if (iobuf_in) {
		assert(f_in == iobuf_f_in);
		return 0;
	}
	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
		out_of_memory("io_start_buffering_in");
	iobuf_f_in = f_in;
	return 1;
}

void io_end_buffering_in(void)
{
	if (!iobuf_in)
		return;
	free(iobuf_in);
	iobuf_in = NULL;
	iobuf_in_ndx = 0;
	iobuf_in_remaining = 0;
	iobuf_f_in = -1;
}

void io_end_buffering_out(void)
{
	if (!iobuf_out)
		return;
	io_flush(FULL_FLUSH);
	free(iobuf_out);
	iobuf_out = NULL;
	iobuf_f_out = -1;
}

void maybe_flush_socket(int important)
{
	if (iobuf_out && iobuf_out_cnt
	 && (important || time(NULL) - last_io_out >= 5))
		io_flush(NORMAL_FLUSH);
}

void maybe_send_keepalive(void)
{
	if (time(NULL) - last_io_out >= allowed_lull) {
		if (!iobuf_out || !iobuf_out_cnt) {
			if (protocol_version < 29)
				send_msg(MSG_DATA, "", 0, 0);
			else if (protocol_version >= 30)
				send_msg(MSG_NOOP, "", 0, 0);
			else {
				write_int(sock_f_out, cur_flist->used);
				write_shortint(sock_f_out, ITEM_IS_NEW);
			}
		}
		if (iobuf_out)
			io_flush(NORMAL_FLUSH);
	}
}

void start_flist_forward(int f_in)
{
	assert(iobuf_out != NULL);
	assert(iobuf_f_out == msg_fd_out);
	flist_forward_from = f_in;
	defer_forwarding_messages++;
}

void stop_flist_forward(void)
{
	flist_forward_from = -1;
	defer_forwarding_messages--;
	io_flush(FULL_FLUSH);
}

/**
 * Continue trying to read len bytes - don't return until len has been
 * read.
 **/
static void read_loop(int fd, char *buf, size_t len)
{
	while (len) {
		int n = read_timeout(fd, buf, len);

		buf += n;
		len -= n;
	}
}

/**
 * Read from the file descriptor handling multiplexing - return number
 * of bytes read.
 *
 * Never returns <= 0.
 */
static int readfd_unbuffered(int fd, char *buf, size_t len)
{
	size_t msg_bytes;
	int tag, cnt = 0;
	char line[BIGPATHBUFLEN];

	if (!iobuf_in || fd != iobuf_f_in)
		return read_timeout(fd, buf, len);

	if (!io_multiplexing_in && iobuf_in_remaining == 0) {
		iobuf_in_remaining = read_timeout(fd, iobuf_in, iobuf_in_siz);
		iobuf_in_ndx = 0;
	}

	while (cnt == 0) {
		if (iobuf_in_remaining) {
			len = MIN(len, iobuf_in_remaining);
			memcpy(buf, iobuf_in + iobuf_in_ndx, len);
			iobuf_in_ndx += len;
			iobuf_in_remaining -= len;
			cnt = len;
			break;
		}

		read_loop(fd, line, 4);
		tag = IVAL(line, 0);

		msg_bytes = tag & 0xFFFFFF;
		tag = (tag >> 24) - MPLEX_BASE;

		switch (tag) {
		case MSG_DATA:
			if (msg_bytes > iobuf_in_siz) {
				if (!(iobuf_in = realloc_array(iobuf_in, char,
							       msg_bytes)))
					out_of_memory("readfd_unbuffered");
				iobuf_in_siz = msg_bytes;
			}
			read_loop(fd, iobuf_in, msg_bytes);
			iobuf_in_remaining = msg_bytes;
			iobuf_in_ndx = 0;
			break;
		case MSG_NOOP:
			if (msg_bytes != 0)
				goto invalid_msg;
			if (am_sender)
				maybe_send_keepalive();
			break;
		case MSG_IO_ERROR:
			if (msg_bytes != 4)
				goto invalid_msg;
			read_loop(fd, line, msg_bytes);
			send_msg_int(MSG_IO_ERROR, IVAL(line, 0));
			io_error |= IVAL(line, 0);
			break;
		case MSG_DELETED:
			if (msg_bytes >= sizeof line)
				goto overflow;
#ifdef ICONV_OPTION
			if (ic_recv != (iconv_t)-1) {
				xbuf outbuf, inbuf;
				char ibuf[512];
				int add_null = 0;

				INIT_CONST_XBUF(outbuf, line);
				INIT_XBUF(inbuf, ibuf, 0, -1);

				while (msg_bytes) {
					inbuf.len = msg_bytes > sizeof ibuf
						  ? sizeof ibuf : msg_bytes;
					read_loop(fd, inbuf.buf, inbuf.len);
					if (!(msg_bytes -= inbuf.len)
					 && !ibuf[inbuf.len-1])
						inbuf.len--, add_null = 1;
					if (iconvbufs(ic_send, &inbuf, &outbuf,
					    ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE) < 0)
						goto overflow;
				}
				if (add_null) {
					if (outbuf.len == outbuf.size)
						goto overflow;
					outbuf.buf[outbuf.len++] = '\0';
				}
				msg_bytes = outbuf.len;
			} else
#endif
				read_loop(fd, line, msg_bytes);
			/* A directory name was sent with the trailing null */
			if (msg_bytes > 0 && !line[msg_bytes-1])
				log_delete(line, S_IFDIR);
			else {
				line[msg_bytes] = '\0';
				log_delete(line, S_IFREG);
			}
			break;
		case MSG_SUCCESS:
			if (msg_bytes != 4) {
			  invalid_msg:
				rprintf(FERROR, "invalid multi-message %d:%ld [%s]\n",
					tag, (long)msg_bytes, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, msg_bytes);
			successful_send(IVAL(line, 0));
			break;
		case MSG_NO_SEND:
			if (msg_bytes != 4)
				goto invalid_msg;
			read_loop(fd, line, msg_bytes);
			send_msg_int(MSG_NO_SEND, IVAL(line, 0));
			break;
		case MSG_INFO:
		case MSG_ERROR:
		case MSG_ERROR_XFER:
		case MSG_WARNING:
			if (msg_bytes >= sizeof line) {
			    overflow:
				rprintf(FERROR,
					"multiplexing overflow %d:%ld [%s]\n",
					tag, (long)msg_bytes, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, msg_bytes);
			rwrite((enum logcode)tag, line, msg_bytes, 1);
			if (first_message) {
				if (list_only && !am_sender && tag == 1) {
					line[msg_bytes] = '\0';
					check_for_d_option_error(line);
				}
				first_message = 0;
			}
			break;
		default:
			rprintf(FERROR, "unexpected tag %d [%s]\n",
				tag, who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
	}

	if (iobuf_in_remaining == 0)
		io_flush(NORMAL_FLUSH);

	return cnt;
}

/* Do a buffered read from fd.  Don't return until all N bytes have
 * been read.  If all N can't be read then exit with an error. */
static void readfd(int fd, char *buffer, size_t N)
{
	int  cnt;
	size_t total = 0;

	while (total < N) {
		cnt = readfd_unbuffered(fd, buffer + total, N-total);
		total += cnt;
	}

	if (fd == write_batch_monitor_in) {
		if ((size_t)write(batch_fd, buffer, total) != total)
			exit_cleanup(RERR_FILEIO);
	}

	if (fd == flist_forward_from)
		writefd(iobuf_f_out, buffer, total);

	if (fd == sock_f_in)
		stats.total_read += total;
}

unsigned short read_shortint(int f)
{
	char b[2];
	readfd(f, b, 2);
	return (UVAL(b, 1) << 8) + UVAL(b, 0);
}

int32 read_int(int f)
{
	char b[4];
	int32 num;

	readfd(f, b, 4);
	num = IVAL(b, 0);
#if SIZEOF_INT32 > 4
	if (num & (int32)0x80000000)
		num |= ~(int32)0xffffffff;
#endif
	return num;
}

int32 read_varint(int f)
{
	union {
	    char b[5];
	    int32 x;
	} u;
	uchar ch;
	int extra;

	u.x = 0;
	readfd(f, (char*)&ch, 1);
	extra = int_byte_extra[ch / 4];
	if (extra) {
		uchar bit = ((uchar)1<<(8-extra));
		if (extra >= (int)sizeof u.b) {
			rprintf(FERROR, "Overflow in read_varint()\n");
			exit_cleanup(RERR_STREAMIO);
		}
		readfd(f, u.b, extra);
		u.b[extra] = ch & (bit-1);
	} else
		u.b[0] = ch;
#if CAREFUL_ALIGNMENT
	u.x = IVAL(u.b,0);
#endif
