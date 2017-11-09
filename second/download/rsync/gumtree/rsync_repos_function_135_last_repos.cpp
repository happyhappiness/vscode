static char *perform_io(size_t needed, int flags)
{
	fd_set r_fds, e_fds, w_fds;
	struct timeval tv;
	int cnt, max_fd;
	size_t empty_buf_len = 0;
	xbuf *out;
	char *data;

	if (iobuf.in.len == 0 && iobuf.in.pos != 0) {
		if (iobuf.raw_input_ends_before)
			iobuf.raw_input_ends_before -= iobuf.in.pos;
		iobuf.in.pos = 0;
	}

	switch (flags & PIO_NEED_FLAGS) {
	case PIO_NEED_INPUT:
		/* We never resize the circular input buffer. */
		if (iobuf.in.size < needed) {
			rprintf(FERROR, "need to read %ld bytes, iobuf.in.buf is only %ld bytes.\n",
				(long)needed, (long)iobuf.in.size);
			exit_cleanup(RERR_PROTOCOL);
		}

		if (msgs2stderr && DEBUG_GTE(IO, 3)) {
			rprintf(FINFO, "[%s] perform_io(%ld, %sinput)\n",
				who_am_i(), (long)needed, flags & PIO_CONSUME_INPUT ? "consume&" : "");
		}
		break;

	case PIO_NEED_OUTROOM:
		/* We never resize the circular output buffer. */
		if (iobuf.out.size - iobuf.out_empty_len < needed) {
			fprintf(stderr, "need to write %ld bytes, iobuf.out.buf is only %ld bytes.\n",
				(long)needed, (long)(iobuf.out.size - iobuf.out_empty_len));
			exit_cleanup(RERR_PROTOCOL);
		}

		if (msgs2stderr && DEBUG_GTE(IO, 3)) {
			rprintf(FINFO, "[%s] perform_io(%ld, outroom) needs to flush %ld\n",
				who_am_i(), (long)needed,
				iobuf.out.len + needed > iobuf.out.size
				? (long)(iobuf.out.len + needed - iobuf.out.size) : 0L);
		}
		break;

	case PIO_NEED_MSGROOM:
		/* We never resize the circular message buffer. */
		if (iobuf.msg.size < needed) {
			fprintf(stderr, "need to write %ld bytes, iobuf.msg.buf is only %ld bytes.\n",
				(long)needed, (long)iobuf.msg.size);
			exit_cleanup(RERR_PROTOCOL);
		}

		if (msgs2stderr && DEBUG_GTE(IO, 3)) {
			rprintf(FINFO, "[%s] perform_io(%ld, msgroom) needs to flush %ld\n",
				who_am_i(), (long)needed,
				iobuf.msg.len + needed > iobuf.msg.size
				? (long)(iobuf.msg.len + needed - iobuf.msg.size) : 0L);
		}
		break;

	case 0:
		if (msgs2stderr && DEBUG_GTE(IO, 3))
			rprintf(FINFO, "[%s] perform_io(%ld, %d)\n", who_am_i(), (long)needed, flags);
		break;

	default:
		exit_cleanup(RERR_UNSUPPORTED);
	}

	while (1) {
		switch (flags & PIO_NEED_FLAGS) {
		case PIO_NEED_INPUT:
			if (iobuf.in.len >= needed)
				goto double_break;
			break;
		case PIO_NEED_OUTROOM:
			/* Note that iobuf.out_empty_len doesn't factor into this check
			 * because iobuf.out.len already holds any needed header len. */
			if (iobuf.out.len + needed <= iobuf.out.size)
				goto double_break;
			break;
		case PIO_NEED_MSGROOM:
			if (iobuf.msg.len + needed <= iobuf.msg.size)
				goto double_break;
			break;
		}

		max_fd = -1;

		FD_ZERO(&r_fds);
		FD_ZERO(&e_fds);
		if (iobuf.in_fd >= 0 && iobuf.in.size - iobuf.in.len) {
			if (!read_batch || batch_fd >= 0) {
				FD_SET(iobuf.in_fd, &r_fds);
				FD_SET(iobuf.in_fd, &e_fds);
			}
			if (iobuf.in_fd > max_fd)
				max_fd = iobuf.in_fd;
		}

		/* Only do more filesfrom processing if there is enough room in the out buffer. */
		if (ff_forward_fd >= 0 && iobuf.out.size - iobuf.out.len > FILESFROM_BUFLEN*2) {
			FD_SET(ff_forward_fd, &r_fds);
			if (ff_forward_fd > max_fd)
				max_fd = ff_forward_fd;
		}

		FD_ZERO(&w_fds);
		if (iobuf.out_fd >= 0) {
			if (iobuf.raw_flushing_ends_before
			 || (!iobuf.msg.len && iobuf.out.len > iobuf.out_empty_len && !(flags & PIO_NEED_MSGROOM))) {
				if (OUT_MULTIPLEXED && !iobuf.raw_flushing_ends_before) {
					/* The iobuf.raw_flushing_ends_before value can point off the end
					 * of the iobuf.out buffer for a while, for easier subtracting. */
					iobuf.raw_flushing_ends_before = iobuf.out.pos + iobuf.out.len;

					SIVAL(iobuf.out.buf + iobuf.raw_data_header_pos, 0,
					      ((MPLEX_BASE + (int)MSG_DATA)<<24) + iobuf.out.len - 4);

					if (msgs2stderr && DEBUG_GTE(IO, 1)) {
						rprintf(FINFO, "[%s] send_msg(%d, %ld)\n",
							who_am_i(), (int)MSG_DATA, (long)iobuf.out.len - 4);
					}

					/* reserve room for the next MSG_DATA header */
					iobuf.raw_data_header_pos = iobuf.raw_flushing_ends_before;
					if (iobuf.raw_data_header_pos >= iobuf.out.size)
						iobuf.raw_data_header_pos -= iobuf.out.size;
					else if (iobuf.raw_data_header_pos + 4 > iobuf.out.size) {
						/* The 4-byte header won't fit at the end of the buffer,
						 * so we'll temporarily reduce the output buffer's size
						 * and put the header at the start of the buffer. */
						reduce_iobuf_size(&iobuf.out, iobuf.raw_data_header_pos);
						iobuf.raw_data_header_pos = 0;
					}
					/* Yes, it is possible for this to make len > size for a while. */
					iobuf.out.len += 4;
				}

				empty_buf_len = iobuf.out_empty_len;
				out = &iobuf.out;
			} else if (iobuf.msg.len) {
				empty_buf_len = 0;
				out = &iobuf.msg;
			} else
				out = NULL;
			if (out) {
				FD_SET(iobuf.out_fd, &w_fds);
				if (iobuf.out_fd > max_fd)
					max_fd = iobuf.out_fd;
			}
		} else
			out = NULL;

		if (max_fd < 0) {
			switch (flags & PIO_NEED_FLAGS) {
			case PIO_NEED_INPUT:
				iobuf.in.len = 0;
				if (kluge_around_eof == 2)
					exit_cleanup(0);
				if (iobuf.in_fd == -2)
					whine_about_eof(True);
				rprintf(FERROR, "error in perform_io: no fd for input.\n");
				exit_cleanup(RERR_PROTOCOL);
			case PIO_NEED_OUTROOM:
			case PIO_NEED_MSGROOM:
				msgs2stderr = 1;
				drain_multiplex_messages();
				if (iobuf.out_fd == -2)
					whine_about_eof(True);
				rprintf(FERROR, "error in perform_io: no fd for output.\n");
				exit_cleanup(RERR_PROTOCOL);
			default:
				/* No stated needs, so I guess this is OK. */
				break;
			}
			break;
		}

		if (got_kill_signal > 0)
			handle_kill_signal(True);

		if (extra_flist_sending_enabled) {
			if (file_total - file_old_total < MAX_FILECNT_LOOKAHEAD && IN_MULTIPLEXED_AND_READY)
				tv.tv_sec = 0;
			else {
				extra_flist_sending_enabled = False;
				tv.tv_sec = select_timeout;
			}
		} else
			tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		cnt = select(max_fd + 1, &r_fds, &w_fds, &e_fds, &tv);

		if (cnt <= 0) {
			if (cnt < 0 && errno == EBADF) {
				msgs2stderr = 1;
				exit_cleanup(RERR_SOCKETIO);
			}
			if (extra_flist_sending_enabled) {
				extra_flist_sending_enabled = False;
				send_extra_file_list(sock_f_out, -1);
				extra_flist_sending_enabled = !flist_eof;
			} else
				check_timeout((flags & PIO_NEED_INPUT) != 0, 0);
			FD_ZERO(&r_fds); /* Just in case... */
			FD_ZERO(&w_fds);
		}

		if (iobuf.in_fd >= 0 && FD_ISSET(iobuf.in_fd, &r_fds)) {
			size_t len, pos = iobuf.in.pos + iobuf.in.len;
			int n;
			if (pos >= iobuf.in.size) {
				pos -= iobuf.in.size;
				len = iobuf.in.size - iobuf.in.len;
			} else
				len = iobuf.in.size - pos;
			if ((n = read(iobuf.in_fd, iobuf.in.buf + pos, len)) <= 0) {
				if (n == 0) {
					/* Signal that input has become invalid. */
					if (!read_batch || batch_fd < 0 || am_generator)
						iobuf.in_fd = -2;
					batch_fd = -1;
					continue;
				}
				if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
					n = 0;
				else {
					/* Don't write errors on a dead socket. */
					if (iobuf.in_fd == sock_f_in) {
						if (am_sender)
							msgs2stderr = 1;
						rsyserr(FERROR_SOCKET, errno, "read error");
					} else
						rsyserr(FERROR, errno, "read error");
					exit_cleanup(RERR_SOCKETIO);
				}
			}
			if (msgs2stderr && DEBUG_GTE(IO, 2))
				rprintf(FINFO, "[%s] recv=%ld\n", who_am_i(), (long)n);

			if (io_timeout) {
				last_io_in = time(NULL);
				if (flags & PIO_NEED_INPUT)
					maybe_send_keepalive(last_io_in, 0);
			}
			stats.total_read += n;

			iobuf.in.len += n;
		}

		if (out && FD_ISSET(iobuf.out_fd, &w_fds)) {
			size_t len = iobuf.raw_flushing_ends_before ? iobuf.raw_flushing_ends_before - out->pos : out->len;
			int n;

			if (bwlimit_writemax && len > bwlimit_writemax)
				len = bwlimit_writemax;

			if (out->pos + len > out->size)
				len = out->size - out->pos;
			if ((n = write(iobuf.out_fd, out->buf + out->pos, len)) <= 0) {
				if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
					n = 0;
				else {
					/* Don't write errors on a dead socket. */
					msgs2stderr = 1;
					iobuf.out_fd = -2;
					iobuf.out.len = iobuf.msg.len = iobuf.raw_flushing_ends_before = 0;
					rsyserr(FERROR_SOCKET, errno, "[%s] write error", who_am_i());
					drain_multiplex_messages();
					exit_cleanup(RERR_SOCKETIO);
				}
			}
			if (msgs2stderr && DEBUG_GTE(IO, 2)) {
				rprintf(FINFO, "[%s] %s sent=%ld\n",
					who_am_i(), out == &iobuf.out ? "out" : "msg", (long)n);
			}

			if (io_timeout)
				last_io_out = time(NULL);
			stats.total_written += n;

			if (bwlimit_writemax)
				sleep_for_bwlimit(n);

			if ((out->pos += n) == out->size) {
				if (iobuf.raw_flushing_ends_before)
					iobuf.raw_flushing_ends_before -= out->size;
				out->pos = 0;
				restore_iobuf_size(out);
			} else if (out->pos == iobuf.raw_flushing_ends_before)
				iobuf.raw_flushing_ends_before = 0;
			if ((out->len -= n) == empty_buf_len) {
				out->pos = 0;
				restore_iobuf_size(out);
				if (empty_buf_len)
					iobuf.raw_data_header_pos = 0;
			}
		}

		if (got_kill_signal > 0)
			handle_kill_signal(True);

		/* We need to help prevent deadlock by doing what reading
		 * we can whenever we are here trying to write. */
		if (IN_MULTIPLEXED_AND_READY && !(flags & PIO_NEED_INPUT)) {
			while (!iobuf.raw_input_ends_before && iobuf.in.len > 512)
				read_a_msg();
			if (flist_receiving_enabled && iobuf.in.len > 512)
				wait_for_receiver(); /* generator only */
		}

		if (ff_forward_fd >= 0 && FD_ISSET(ff_forward_fd, &r_fds)) {
			/* This can potentially flush all output and enable
			 * multiplexed output, so keep this last in the loop
			 * and be sure to not cache anything that would break
			 * such a change. */
			forward_filesfrom_data();
		}
	}
  double_break:

	if (got_kill_signal > 0)
		handle_kill_signal(True);

	data = iobuf.in.buf + iobuf.in.pos;

	if (flags & PIO_CONSUME_INPUT) {
		iobuf.in.len -= needed;
		iobuf.in.pos += needed;
		if (iobuf.in.pos == iobuf.raw_input_ends_before)
			iobuf.raw_input_ends_before = 0;
		if (iobuf.in.pos >= iobuf.in.size) {
			iobuf.in.pos -= iobuf.in.size;
			if (iobuf.raw_input_ends_before)
				iobuf.raw_input_ends_before -= iobuf.in.size;
		}
	}

	return data;
}