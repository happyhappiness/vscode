			FD_ZERO(&e_fds);
			FD_SET(fd, &e_fds);
			tv.tv_sec = select_timeout;
			tv.tv_usec = 0;
			if (!select(fd+1, &r_fds, NULL, &e_fds, &tv))
				check_timeout();
			if (FD_ISSET(fd, &e_fds)) {
				rsyserr(FINFO, errno,
					"select exception on fd %d", fd);
			}
			continue;
		}
		if (cnt != 1)
			break;
		if (nulls? !ch : (ch == '\r' || ch == '\n')) {
			/* Skip empty lines if reading locally. */
			if (!reading_remotely && s == fname)
				continue;
			break;
		}
		if (s < eob)
			*s++ = ch;
	}
	*s = '\0';

	/* Dump comments. */
	if (*fname == '#' || *fname == ';')
		goto start;

	return s - fname;
}

static char *iobuf_out;
static int iobuf_out_cnt;

void io_start_buffering_out(void)
{
	if (iobuf_out)
		return;
	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
		out_of_memory("io_start_buffering_out");
	iobuf_out_cnt = 0;
}

static char *iobuf_in;
static size_t iobuf_in_siz;

void io_start_buffering_in(void)
{
	if (iobuf_in)
		return;
	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
		out_of_memory("io_start_buffering_in");
}

void io_end_buffering(void)
{
	io_flush(NORMAL_FLUSH);
	if (!io_multiplexing_out) {
		free(iobuf_out);
		iobuf_out = NULL;
	}
}

void maybe_flush_socket(void)
{
	if (iobuf_out && iobuf_out_cnt && time(NULL) - last_io_out >= 5)
		io_flush(NORMAL_FLUSH);
}

void maybe_send_keepalive(void)
{
	if (time(NULL) - last_io_out >= allowed_lull) {
		if (!iobuf_out || !iobuf_out_cnt) {
			if (protocol_version < 29)
				return; /* there's nothing we can do */
			write_int(sock_f_out, the_file_list->count);
			write_shortint(sock_f_out, ITEM_IS_NEW);
		}
		if (iobuf_out)
			io_flush(NORMAL_FLUSH);
	}
}

/**
 * Continue trying to read len bytes - don't return until len has been
 * read.
 **/
static void read_loop(int fd, char *buf, size_t len)
{
