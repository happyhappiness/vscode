static int readfd_unbuffered(int fd, char *buf, size_t len)
{
	static size_t remaining;
	static size_t iobuf_in_ndx;
	size_t msg_bytes;
	int tag, ret = 0;
#if MAXPATHLEN < 4096
	char line[4096+1024];
#else
	char line[MAXPATHLEN+1024];
#endif

	if (!iobuf_in || fd != sock_f_in)
		return read_timeout(fd, buf, len);

	if (!io_multiplexing_in && remaining == 0) {
		remaining = read_timeout(fd, iobuf_in, iobuf_in_siz);
		iobuf_in_ndx = 0;
	}

	while (ret == 0) {
		if (remaining) {
			len = MIN(len, remaining);
			memcpy(buf, iobuf_in + iobuf_in_ndx, len);
			iobuf_in_ndx += len;
			remaining -= len;
			ret = len;
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
			remaining = msg_bytes;
			iobuf_in_ndx = 0;
			break;
		case MSG_DELETED:
			if (msg_bytes >= sizeof line)
				goto overflow;
			read_loop(fd, line, msg_bytes);
			line[msg_bytes] = '\0';
			/* A directory name was sent with the trailing null */
			if (msg_bytes > 0 && !line[msg_bytes-1])
				log_delete(line, S_IFDIR);
			else
				log_delete(line, S_IFREG);
			break;
		case MSG_SUCCESS:
			if (msg_bytes != 4) {
				rprintf(FERROR, "invalid multi-message %d:%ld [%s]\n",
					tag, (long)msg_bytes, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, msg_bytes);
			successful_send(IVAL(line, 0));
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (msg_bytes >= sizeof line) {
			    overflow:
				rprintf(FERROR,
					"multiplexing overflow %d:%ld [%s]\n",
					tag, (long)msg_bytes, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, msg_bytes);
			rwrite((enum logcode)tag, line, msg_bytes);
			break;
		default:
			rprintf(FERROR, "unexpected tag %d [%s]\n",
				tag, who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
	}

	if (remaining == 0)
		io_flush(NORMAL_FLUSH);

	return ret;
}