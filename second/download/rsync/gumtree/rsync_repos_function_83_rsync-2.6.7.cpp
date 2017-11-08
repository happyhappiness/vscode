static void read_msg_fd(void)
{
	char buf[2048];
	size_t n;
	int fd = msg_fd_in;
	int tag, len;

	/* Temporarily disable msg_fd_in.  This is needed to avoid looping back
	 * to this routine from writefd_unbuffered(). */
	msg_fd_in = -1;

	read_loop(fd, buf, 4);
	tag = IVAL(buf, 0);

	len = tag & 0xFFFFFF;
	tag = (tag >> 24) - MPLEX_BASE;

	switch (tag) {
	case MSG_DONE:
		if (len != 0 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		flist_ndx_push(&redo_list, -1);
		break;
	case MSG_REDO:
		if (len != 4 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, 4);
		if (remove_sent_files)
			decrement_active_files(IVAL(buf,0));
		flist_ndx_push(&redo_list, IVAL(buf,0));
		break;
	case MSG_DELETED:
		if (len >= (int)sizeof buf || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, len);
		io_multiplex_write(MSG_DELETED, buf, len);
		break;
	case MSG_SUCCESS:
		if (len != 4 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, len);
		if (remove_sent_files) {
			decrement_active_files(IVAL(buf,0));
			io_multiplex_write(MSG_SUCCESS, buf, len);
		}
		if (preserve_hard_links)
			flist_ndx_push(&hlink_list, IVAL(buf,0));
		break;
	case MSG_SOCKERR:
		if (!am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		close_multiplexing_out();
		/* FALL THROUGH */
	case MSG_INFO:
	case MSG_ERROR:
	case MSG_LOG:
		while (len) {
			n = len;
			if (n >= sizeof buf)
				n = sizeof buf - 1;
			read_loop(fd, buf, n);
			rwrite((enum logcode)tag, buf, n);
			len -= n;
		}
		break;
	default:
		rprintf(FERROR, "unknown message %d:%d\n", tag, len);
		exit_cleanup(RERR_STREAMIO);
	}

	msg_fd_in = fd;
}