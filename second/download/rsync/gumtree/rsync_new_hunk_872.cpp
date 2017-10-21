{
	msg_fd_out = fd;
	set_nonblocking(msg_fd_out);
}

/* Add a message to the pending MSG_* list. */
static void msg_list_add(struct msg_list *lst, int code, const char *buf, int len, int convert)
{
	struct msg_list_item *m;
	int sz = len + 4 + sizeof m[0] - 1;

	if (!(m = (struct msg_list_item *)new_array(char, sz)))
		out_of_memory("msg_list_add");
	m->next = NULL;
	m->convert = convert;
	SIVAL(m->buf, 0, ((code+MPLEX_BASE)<<24) | len);
	memcpy(m->buf + 4, buf, len);
	if (lst->tail)
		lst->tail->next = m;
	else
		lst->head = m;
	lst->tail = m;
}

static void msg_flush(void)
{
	if (am_generator) {
		while (msg_queue.head && io_multiplexing_out) {
			struct msg_list_item *m = msg_queue.head;
			int len = IVAL(m->buf, 0) & 0xFFFFFF;
			int tag = *((uchar*)m->buf+3) - MPLEX_BASE;
			if (!(msg_queue.head = m->next))
				msg_queue.tail = NULL;
			stats.total_written += len + 4;
			defer_forwarding_messages++;
			mplex_write(sock_f_out, tag, m->buf + 4, len, m->convert);
			defer_forwarding_messages--;
			free(m);
		}
	} else {
		while (msg_queue.head) {
			struct msg_list_item *m = msg_queue.head;
			int len = IVAL(m->buf, 0) & 0xFFFFFF;
			int tag = *((uchar*)m->buf+3) - MPLEX_BASE;
			if (!(msg_queue.head = m->next))
				msg_queue.tail = NULL;
			defer_forwarding_messages++;
			mplex_write(msg_fd_out, tag, m->buf + 4, len, m->convert);
			defer_forwarding_messages--;
			free(m);
		}
	}
}

/* Read a message from the MSG_* fd and handle it.  This is called either
 * during the early stages of being a local sender (up through the sending
 * of the file list) or when we're the generator (to fetch the messages
 * from the receiver). */
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

/* This is used by the generator to limit how many file transfers can
 * be active at once when --remove-source-files is specified.  Without
 * this, sender-side deletions were mostly happening at the end. */
void increment_active_files(int ndx, int itemizing, enum logcode code)
{
	/* TODO: tune these limits? */
	while (active_filecnt >= (active_bytecnt >= 128*1024 ? 10 : 50)) {
		check_for_finished_files(itemizing, code, 0);
		if (iobuf_out_cnt)
			io_flush(NORMAL_FLUSH);
		else
			read_msg_fd();
	}

	active_filecnt++;
	active_bytecnt += F_LENGTH(cur_flist->files[ndx - cur_flist->ndx_start]);
}

/* Write an message to a multiplexed stream. If this fails, rsync exits. */
static void mplex_write(int fd, enum msgcode code, const char *buf, size_t len, int convert)
{
	char buffer[BIGPATHBUFLEN]; /* Oversized for use by iconv code. */
	size_t n = len;

#ifdef ICONV_OPTION
	/* We need to convert buf before doing anything else so that we
	 * can include the (converted) byte length in the message header. */
	if (convert && ic_send != (iconv_t)-1) {
		xbuf outbuf, inbuf;

		INIT_XBUF(outbuf, buffer + 4, 0, sizeof buffer - 4);
		INIT_XBUF(inbuf, (char*)buf, len, -1);

		iconvbufs(ic_send, &inbuf, &outbuf,
			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
		if (inbuf.len > 0) {
			rprintf(FERROR, "overflowed conversion buffer in mplex_write");
			exit_cleanup(RERR_UNSUPPORTED);
		}

		n = len = outbuf.len;
	} else
#endif
	if (n > 1024 - 4) /* BIGPATHBUFLEN can handle 1024 bytes */
		n = 0;    /* We'd rather do 2 writes than too much memcpy(). */
	else
		memcpy(buffer + 4, buf, n);

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	defer_forwarding_keep = 1; /* defer_forwarding_messages++ on return */
	writefd_unbuffered(fd, buffer, n+4);
	defer_forwarding_keep = 0;

	if (len > n)
		writefd_unbuffered(fd, buf+n, len-n);

	if (!--defer_forwarding_messages && !no_flush)
		msg_flush();
}

int send_msg(enum msgcode code, const char *buf, int len, int convert)
{
	if (msg_fd_out < 0) {
		if (!defer_forwarding_messages)
			return io_multiplex_write(code, buf, len, convert);
		if (!io_multiplexing_out)
			return 0;
		msg_list_add(&msg_queue, code, buf, len, convert);
		return 1;
	}
	if (flist_forward_from >= 0)
		msg_list_add(&msg_queue, code, buf, len, convert);
	else
		mplex_write(msg_fd_out, code, buf, len, convert);
	return 1;
}

void send_msg_int(enum msgcode code, int num)
{
	char numbuf[4];
	SIVAL(numbuf, 0, num);
	send_msg(code, numbuf, 4, 0);
}

void wait_for_receiver(void)
{
	if (iobuf_out_cnt)
		io_flush(NORMAL_FLUSH);
	else
		read_msg_fd();
}

int get_redo_num(void)
{
	return flist_ndx_pop(&redo_list);
}

int get_hlink_num(void)
{
	return flist_ndx_pop(&hlink_list);
