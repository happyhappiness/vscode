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