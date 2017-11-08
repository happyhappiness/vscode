static void read_msg_fd(void)
{
	char buf[2048];
	size_t n;
	struct file_list *flist;
	int fd = msg_fd_in;
	int tag, len;

	/* Temporarily disable msg_fd_in.  This is needed to avoid looping back
	 * to this routine from writefd_unbuffered(). */
	no_flush++;
	msg_fd_in = -1;
	defer_forwarding_messages++;

	readfd(fd, buf, 4);
	tag = IVAL(buf, 0);

	len = tag & 0xFFFFFF;
	tag = (tag >> 24) - MPLEX_BASE;

	switch (tag) {
	case MSG_DONE:
		if (len < 0 || len > 1 || !am_generator) {
		  invalid_msg:
			rprintf(FERROR, "invalid message %d:%d [%s%s]\n",
				tag, len, who_am_i(),
				inc_recurse ? "/inc" : "");
			exit_cleanup(RERR_STREAMIO);
		}
		if (len) {
			readfd(fd, buf, len);
			stats.total_read = read_varlong(fd, 3);
		}
		msgdone_cnt++;
		break;
	case MSG_REDO:
		if (len != 4 || !am_generator)
			goto invalid_msg;
		readfd(fd, buf, 4);
		got_flist_entry_status(FES_REDO, buf);
		break;
	case MSG_FLIST:
		if (len != 4 || !am_generator || !inc_recurse)
			goto invalid_msg;
		readfd(fd, buf, 4);
		/* Read extra file list from receiver. */
		assert(iobuf_in != NULL);
		assert(iobuf_f_in == fd);
		if (verbose > 3) {
			rprintf(FINFO, "[%s] receiving flist for dir %d\n",
				who_am_i(), IVAL(buf,0));
		}
		flist = recv_file_list(fd);
		flist->parent_ndx = IVAL(buf,0);
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links)
			match_hard_links(flist);
#endif
		break;
	case MSG_FLIST_EOF:
		if (len != 0 || !am_generator || !inc_recurse)
			goto invalid_msg;
		flist_eof = 1;
		break;
	case MSG_IO_ERROR:
		if (len != 4)
			goto invalid_msg;
		readfd(fd, buf, len);
		io_error |= IVAL(buf, 0);
		break;
	case MSG_DELETED:
		if (len >= (int)sizeof buf || !am_generator)
			goto invalid_msg;
		readfd(fd, buf, len);
		send_msg(MSG_DELETED, buf, len, 1);
		break;
	case MSG_SUCCESS:
		if (len != 4 || !am_generator)
			goto invalid_msg;
		readfd(fd, buf, 4);
		got_flist_entry_status(FES_SUCCESS, buf);
		break;
	case MSG_NO_SEND:
		if (len != 4 || !am_generator)
			goto invalid_msg;
		readfd(fd, buf, 4);
		got_flist_entry_status(FES_NO_SEND, buf);
		break;
	case MSG_ERROR_SOCKET:
	case MSG_ERROR_UTF8:
	case MSG_CLIENT:
		if (!am_generator)
			goto invalid_msg;
		if (tag == MSG_ERROR_SOCKET)
			io_end_multiplex_out();
		/* FALL THROUGH */
	case MSG_INFO:
	case MSG_ERROR:
	case MSG_ERROR_XFER:
	case MSG_WARNING:
	case MSG_LOG:
		while (len) {
			n = len;
			if (n >= sizeof buf)
				n = sizeof buf - 1;
			readfd(fd, buf, n);
			rwrite((enum logcode)tag, buf, n, !am_generator);
			len -= n;
		}
		break;
	default:
		rprintf(FERROR, "unknown message %d:%d [%s]\n",
			tag, len, who_am_i());
		exit_cleanup(RERR_STREAMIO);
	}

	no_flush--;
	msg_fd_in = fd;
	if (!--defer_forwarding_messages && !no_flush)
		msg_flush();
}