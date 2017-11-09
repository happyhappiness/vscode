static void read_a_msg(void)
{
	char data[BIGPATHBUFLEN];
	int tag, val;
	size_t msg_bytes;

	/* This ensures that perform_io() does not try to do any message reading
	 * until we've read all of the data for this message.  We should also
	 * try to avoid calling things that will cause data to be written via
	 * perform_io() prior to this being reset to 1. */
	iobuf.in_multiplexed = -1;

	tag = raw_read_int();

	msg_bytes = tag & 0xFFFFFF;
	tag = (tag >> 24) - MPLEX_BASE;

	if (DEBUG_GTE(IO, 1) && msgs2stderr)
		rprintf(FINFO, "[%s] got msg=%d, len=%ld\n", who_am_i(), (int)tag, (long)msg_bytes);

	switch (tag) {
	case MSG_DATA:
		assert(iobuf.raw_input_ends_before == 0);
		/* Though this does not yet read the data, we do mark where in
		 * the buffer the msg data will end once it is read.  It is
		 * possible that this points off the end of the buffer, in
		 * which case the gradual reading of the input stream will
		 * cause this value to wrap around and eventually become real. */
		if (msg_bytes)
			iobuf.raw_input_ends_before = iobuf.in.pos + msg_bytes;
		iobuf.in_multiplexed = 1;
		break;
	case MSG_STATS:
		if (msg_bytes != sizeof stats.total_read || !am_generator)
			goto invalid_msg;
		raw_read_buf((char*)&stats.total_read, sizeof stats.total_read);
		iobuf.in_multiplexed = 1;
		break;
	case MSG_REDO:
		if (msg_bytes != 4 || !am_generator)
			goto invalid_msg;
		val = raw_read_int();
		iobuf.in_multiplexed = 1;
		got_flist_entry_status(FES_REDO, val);
		break;
	case MSG_IO_ERROR:
		if (msg_bytes != 4)
			goto invalid_msg;
		val = raw_read_int();
		iobuf.in_multiplexed = 1;
		io_error |= val;
		if (am_receiver)
			send_msg_int(MSG_IO_ERROR, val);
		break;
	case MSG_IO_TIMEOUT:
		if (msg_bytes != 4 || am_server || am_generator)
			goto invalid_msg;
		val = raw_read_int();
		iobuf.in_multiplexed = 1;
		if (!io_timeout || io_timeout > val) {
			if (INFO_GTE(MISC, 2))
				rprintf(FINFO, "Setting --timeout=%d to match server\n", val);
			set_io_timeout(val);
		}
		break;
	case MSG_NOOP:
		/* Support protocol-30 keep-alive method. */
		if (msg_bytes != 0)
			goto invalid_msg;
		iobuf.in_multiplexed = 1;
		if (am_sender)
			maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
		break;
	case MSG_DELETED:
		if (msg_bytes >= sizeof data)
			goto overflow;
		if (am_generator) {
			raw_read_buf(data, msg_bytes);
			iobuf.in_multiplexed = 1;
			send_msg(MSG_DELETED, data, msg_bytes, 1);
			break;
		}
#ifdef ICONV_OPTION
		if (ic_recv != (iconv_t)-1) {
			xbuf outbuf, inbuf;
			char ibuf[512];
			int add_null = 0;
			int flags = ICB_INCLUDE_BAD | ICB_INIT;

			INIT_CONST_XBUF(outbuf, data);
			INIT_XBUF(inbuf, ibuf, 0, (size_t)-1);

			while (msg_bytes) {
				size_t len = msg_bytes > sizeof ibuf - inbuf.len ? sizeof ibuf - inbuf.len : msg_bytes;
				raw_read_buf(ibuf + inbuf.len, len);
				inbuf.pos = 0;
				inbuf.len += len;
				if (!(msg_bytes -= len) && !ibuf[inbuf.len-1])
					inbuf.len--, add_null = 1;
				if (iconvbufs(ic_send, &inbuf, &outbuf, flags) < 0) {
					if (errno == E2BIG)
						goto overflow;
					/* Buffer ended with an incomplete char, so move the
					 * bytes to the start of the buffer and continue. */
					memmove(ibuf, ibuf + inbuf.pos, inbuf.len);
				}
				flags &= ~ICB_INIT;
			}
			if (add_null) {
				if (outbuf.len == outbuf.size)
					goto overflow;
				outbuf.buf[outbuf.len++] = '\0';
			}
			msg_bytes = outbuf.len;
		} else
#endif
			raw_read_buf(data, msg_bytes);
		iobuf.in_multiplexed = 1;
		/* A directory name was sent with the trailing null */
		if (msg_bytes > 0 && !data[msg_bytes-1])
			log_delete(data, S_IFDIR);
		else {
			data[msg_bytes] = '\0';
			log_delete(data, S_IFREG);
		}
		break;
	case MSG_SUCCESS:
		if (msg_bytes != 4) {
		  invalid_msg:
			rprintf(FERROR, "invalid multi-message %d:%lu [%s%s]\n",
				tag, (unsigned long)msg_bytes, who_am_i(),
				inc_recurse ? "/inc" : "");
			exit_cleanup(RERR_STREAMIO);
		}
		val = raw_read_int();
		iobuf.in_multiplexed = 1;
		if (am_generator)
			got_flist_entry_status(FES_SUCCESS, val);
		else
			successful_send(val);
		break;
	case MSG_NO_SEND:
		if (msg_bytes != 4)
			goto invalid_msg;
		val = raw_read_int();
		iobuf.in_multiplexed = 1;
		if (am_generator)
			got_flist_entry_status(FES_NO_SEND, val);
		else
			send_msg_int(MSG_NO_SEND, val);
		break;
	case MSG_ERROR_SOCKET:
	case MSG_ERROR_UTF8:
	case MSG_CLIENT:
	case MSG_LOG:
		if (!am_generator)
			goto invalid_msg;
		if (tag == MSG_ERROR_SOCKET)
			msgs2stderr = 1;
		/* FALL THROUGH */
	case MSG_INFO:
	case MSG_ERROR:
	case MSG_ERROR_XFER:
	case MSG_WARNING:
		if (msg_bytes >= sizeof data) {
		    overflow:
			rprintf(FERROR,
				"multiplexing overflow %d:%lu [%s%s]\n",
				tag, (unsigned long)msg_bytes, who_am_i(),
				inc_recurse ? "/inc" : "");
			exit_cleanup(RERR_STREAMIO);
		}
		raw_read_buf(data, msg_bytes);
		/* We don't set in_multiplexed value back to 1 before writing this message
		 * because the write might loop back and read yet another message, over and
		 * over again, while waiting for room to put the message in the msg buffer. */
		rwrite((enum logcode)tag, data, msg_bytes, !am_generator);
		iobuf.in_multiplexed = 1;
		if (first_message) {
			if (list_only && !am_sender && tag == 1 && msg_bytes < sizeof data) {
				data[msg_bytes] = '\0';
				check_for_d_option_error(data);
			}
			first_message = 0;
		}
		break;
	case MSG_ERROR_EXIT:
		if (msg_bytes == 4)
			val = raw_read_int();
		else if (msg_bytes == 0)
			val = 0;
		else
			goto invalid_msg;
		iobuf.in_multiplexed = 1;
		if (DEBUG_GTE(EXIT, 3))
			rprintf(FINFO, "[%s] got MSG_ERROR_EXIT with %ld bytes\n", who_am_i(), (long)msg_bytes);
		if (msg_bytes == 0) {
			if (!am_sender && !am_generator) {
				if (DEBUG_GTE(EXIT, 3)) {
					rprintf(FINFO, "[%s] sending MSG_ERROR_EXIT (len 0)\n",
						who_am_i());
				}
				send_msg(MSG_ERROR_EXIT, "", 0, 0);
				io_flush(FULL_FLUSH);
			}
		} else if (protocol_version >= 31) {
			if (am_generator || am_receiver) {
				if (DEBUG_GTE(EXIT, 3)) {
					rprintf(FINFO, "[%s] sending MSG_ERROR_EXIT with exit_code %d\n",
						who_am_i(), val);
				}
				send_msg_int(MSG_ERROR_EXIT, val);
			} else {
				if (DEBUG_GTE(EXIT, 3)) {
					rprintf(FINFO, "[%s] sending MSG_ERROR_EXIT (len 0)\n",
						who_am_i());
				}
				send_msg(MSG_ERROR_EXIT, "", 0, 0);
			}
		}
		/* Send a negative linenum so that we don't end up
		 * with a duplicate exit message. */
		_exit_cleanup(val, __FILE__, 0 - __LINE__);
	default:
		rprintf(FERROR, "unexpected tag %d [%s%s]\n",
			tag, who_am_i(), inc_recurse ? "/inc" : "");
		exit_cleanup(RERR_STREAMIO);
	}

	assert(iobuf.in_multiplexed > 0);
}