 	glob_expand(NULL, NULL, NULL, NULL);
 
 	*argc_p = argc;
 	*argv_p = argv;
 }
 
-int io_start_buffering_out(int f_out)
+BOOL io_start_buffering_out(int f_out)
 {
-	if (iobuf_out) {
-		assert(f_out == iobuf_f_out);
-		return 0;
+	if (msgs2stderr && DEBUG_GTE(IO, 2))
+		rprintf(FINFO, "[%s] io_start_buffering_out(%d)\n", who_am_i(), f_out);
+
+	if (iobuf.out.buf) {
+		if (iobuf.out_fd == -1)
+			iobuf.out_fd = f_out;
+		else
+			assert(f_out == iobuf.out_fd);
+		return False;
 	}
-	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
-		out_of_memory("io_start_buffering_out");
-	iobuf_out_cnt = 0;
-	iobuf_f_out = f_out;
-	return 1;
+
+	alloc_xbuf(&iobuf.out, ROUND_UP_1024(IO_BUFFER_SIZE * 2));
+	iobuf.out_fd = f_out;
+
+	return True;
+}
+
+BOOL io_start_buffering_in(int f_in)
+{
+	if (msgs2stderr && DEBUG_GTE(IO, 2))
+		rprintf(FINFO, "[%s] io_start_buffering_in(%d)\n", who_am_i(), f_in);
+
+	if (iobuf.in.buf) {
+		if (iobuf.in_fd == -1)
+			iobuf.in_fd = f_in;
+		else
+			assert(f_in == iobuf.in_fd);
+		return False;
+	}
+
+	alloc_xbuf(&iobuf.in, ROUND_UP_1024(IO_BUFFER_SIZE));
+	iobuf.in_fd = f_in;
+
+	return True;
 }
 
-int io_start_buffering_in(int f_in)
+void io_end_buffering_in(BOOL free_buffers)
 {
-	if (iobuf_in) {
-		assert(f_in == iobuf_f_in);
-		return 0;
+	if (msgs2stderr && DEBUG_GTE(IO, 2)) {
+		rprintf(FINFO, "[%s] io_end_buffering_in(IOBUF_%s_BUFS)\n",
+			who_am_i(), free_buffers ? "FREE" : "KEEP");
 	}
-	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
-	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
-		out_of_memory("io_start_buffering_in");
-	iobuf_f_in = f_in;
-	return 1;
-}
 
-void io_end_buffering_in(void)
-{
-	if (!iobuf_in)
-		return;
-	free(iobuf_in);
-	iobuf_in = NULL;
-	iobuf_in_ndx = 0;
-	iobuf_in_remaining = 0;
-	iobuf_f_in = -1;
+	if (free_buffers)
+		free_xbuf(&iobuf.in);
+	else
+		iobuf.in.pos = iobuf.in.len = 0;
+
+	iobuf.in_fd = -1;
 }
 
-void io_end_buffering_out(void)
+void io_end_buffering_out(BOOL free_buffers)
 {
-	if (!iobuf_out)
-		return;
+	if (msgs2stderr && DEBUG_GTE(IO, 2)) {
+		rprintf(FINFO, "[%s] io_end_buffering_out(IOBUF_%s_BUFS)\n",
+			who_am_i(), free_buffers ? "FREE" : "KEEP");
+	}
+
 	io_flush(FULL_FLUSH);
-	free(iobuf_out);
-	iobuf_out = NULL;
-	iobuf_f_out = -1;
+
+	if (free_buffers) {
+		free_xbuf(&iobuf.out);
+		free_xbuf(&iobuf.msg);
+	}
+
+	iobuf.out_fd = -1;
 }
 
 void maybe_flush_socket(int important)
 {
-	if (iobuf_out && iobuf_out_cnt
+	if (flist_eof && iobuf.out.buf && iobuf.out.len > iobuf.out_empty_len
 	 && (important || time(NULL) - last_io_out >= 5))
 		io_flush(NORMAL_FLUSH);
 }
 
-void maybe_send_keepalive(void)
-{
-	if (time(NULL) - last_io_out >= allowed_lull) {
-		if (!iobuf_out || !iobuf_out_cnt) {
-			if (protocol_version < 29)
-				send_msg(MSG_DATA, "", 0, 0);
-			else if (protocol_version >= 30)
-				send_msg(MSG_NOOP, "", 0, 0);
-			else {
-				write_int(sock_f_out, cur_flist->used);
-				write_shortint(sock_f_out, ITEM_IS_NEW);
-			}
-		}
-		if (iobuf_out)
+/* Older rsync versions used to send either a MSG_NOOP (protocol 30) or a
+ * raw-data-based keep-alive (protocol 29), both of which implied forwarding of
+ * the message through the sender.  Since the new timeout method does not need
+ * any forwarding, we just send an empty MSG_DATA message, which works with all
+ * rsync versions.  This avoids any message forwarding, and leaves the raw-data
+ * stream alone (since we can never be quite sure if that stream is in the
+ * right state for a keep-alive message). */
+void maybe_send_keepalive(time_t now, int flags)
+{
+	if (flags & MSK_ACTIVE_RECEIVER)
+		last_io_in = now; /* Fudge things when we're working hard on the files. */
+
+	if (now - last_io_out >= allowed_lull) {
+		/* The receiver is special:  it only sends keep-alive messages if it is
+		 * actively receiving data.  Otherwise, it lets the generator timeout. */
+		if (am_receiver && now - last_io_in >= io_timeout)
+			return;
+
+		if (!iobuf.msg.len && iobuf.out.len == iobuf.out_empty_len)
+			send_msg(MSG_DATA, "", 0, 0);
+		if (!(flags & MSK_ALLOW_FLUSH)) {
+			/* Let the caller worry about writing out the data. */
+		} else if (iobuf.msg.len)
+			perform_io(iobuf.msg.size - iobuf.msg.len + 1, PIO_NEED_MSGROOM);
+		else if (iobuf.out.len > iobuf.out_empty_len)
 			io_flush(NORMAL_FLUSH);
 	}
 }
 
-void start_flist_forward(int f_in)
+void start_flist_forward(int ndx)
 {
-	assert(iobuf_out != NULL);
-	assert(iobuf_f_out == msg_fd_out);
-	flist_forward_from = f_in;
-	defer_forwarding_messages++;
+	write_int(iobuf.out_fd, ndx);
+	forward_flist_data = 1;
 }
 
 void stop_flist_forward(void)
 {
-	flist_forward_from = -1;
-	defer_forwarding_messages--;
-	io_flush(FULL_FLUSH);
-}
-
-/**
- * Continue trying to read len bytes - don't return until len has been
- * read.
- **/
-static void read_loop(int fd, char *buf, size_t len)
-{
-	while (len) {
-		int n = read_timeout(fd, buf, len);
-
-		buf += n;
-		len -= n;
-	}
+	forward_flist_data = 0;
 }
 
-/**
- * Read from the file descriptor handling multiplexing - return number
- * of bytes read.
- *
- * Never returns <= 0.
- */
-static int readfd_unbuffered(int fd, char *buf, size_t len)
+/* Read a message from a multiplexed source. */
+static void read_a_msg(void)
 {
+	char data[BIGPATHBUFLEN];
+	int tag, val;
 	size_t msg_bytes;
-	int tag, cnt = 0;
-	char line[BIGPATHBUFLEN];
 
-	if (!iobuf_in || fd != iobuf_f_in)
-		return read_timeout(fd, buf, len);
+	/* This ensures that perform_io() does not try to do any message reading
+	 * until we've read all of the data for this message.  We should also
+	 * try to avoid calling things that will cause data to be written via
+	 * perform_io() prior to this being reset to 1. */
+	iobuf.in_multiplexed = -1;
 
-	if (!io_multiplexing_in && iobuf_in_remaining == 0) {
-		iobuf_in_remaining = read_timeout(fd, iobuf_in, iobuf_in_siz);
-		iobuf_in_ndx = 0;
-	}
-
-	while (cnt == 0) {
-		if (iobuf_in_remaining) {
-			len = MIN(len, iobuf_in_remaining);
-			memcpy(buf, iobuf_in + iobuf_in_ndx, len);
-			iobuf_in_ndx += len;
-			iobuf_in_remaining -= len;
-			cnt = len;
-			break;
-		}
+	tag = raw_read_int();
 
-		read_loop(fd, line, 4);
-		tag = IVAL(line, 0);
+	msg_bytes = tag & 0xFFFFFF;
+	tag = (tag >> 24) - MPLEX_BASE;
 
-		msg_bytes = tag & 0xFFFFFF;
-		tag = (tag >> 24) - MPLEX_BASE;
+	if (DEBUG_GTE(IO, 1) && msgs2stderr)
+		rprintf(FINFO, "[%s] got msg=%d, len=%ld\n", who_am_i(), (int)tag, (long)msg_bytes);
 
-		switch (tag) {
-		case MSG_DATA:
-			if (msg_bytes > iobuf_in_siz) {
-				if (!(iobuf_in = realloc_array(iobuf_in, char,
-							       msg_bytes)))
-					out_of_memory("readfd_unbuffered");
-				iobuf_in_siz = msg_bytes;
-			}
-			read_loop(fd, iobuf_in, msg_bytes);
-			iobuf_in_remaining = msg_bytes;
-			iobuf_in_ndx = 0;
-			break;
-		case MSG_NOOP:
-			if (msg_bytes != 0)
-				goto invalid_msg;
-			if (am_sender)
-				maybe_send_keepalive();
-			break;
-		case MSG_IO_ERROR:
-			if (msg_bytes != 4)
-				goto invalid_msg;
-			read_loop(fd, line, msg_bytes);
-			send_msg_int(MSG_IO_ERROR, IVAL(line, 0));
-			io_error |= IVAL(line, 0);
+	switch (tag) {
+	case MSG_DATA:
+		assert(iobuf.raw_input_ends_before == 0);
+		/* Though this does not yet read the data, we do mark where in
+		 * the buffer the msg data will end once it is read.  It is
+		 * possible that this points off the end of the buffer, in
+		 * which case the gradual reading of the input stream will
+		 * cause this value to wrap around and eventually become real. */
+		if (msg_bytes)
+			iobuf.raw_input_ends_before = iobuf.in.pos + msg_bytes;
+		iobuf.in_multiplexed = 1;
+		break;
+	case MSG_STATS:
+		if (msg_bytes != sizeof stats.total_read || !am_generator)
+			goto invalid_msg;
+		raw_read_buf((char*)&stats.total_read, sizeof stats.total_read);
+		iobuf.in_multiplexed = 1;
+		break;
+	case MSG_REDO:
+		if (msg_bytes != 4 || !am_generator)
+			goto invalid_msg;
+		val = raw_read_int();
+		iobuf.in_multiplexed = 1;
+		got_flist_entry_status(FES_REDO, val);
+		break;
+	case MSG_IO_ERROR:
+		if (msg_bytes != 4)
+			goto invalid_msg;
+		val = raw_read_int();
+		iobuf.in_multiplexed = 1;
+		io_error |= val;
+		if (am_receiver)
+			send_msg_int(MSG_IO_ERROR, val);
+		break;
+	case MSG_IO_TIMEOUT:
+		if (msg_bytes != 4 || am_server || am_generator)
+			goto invalid_msg;
+		val = raw_read_int();
+		iobuf.in_multiplexed = 1;
+		if (!io_timeout || io_timeout > val) {
+			if (INFO_GTE(MISC, 2))
+				rprintf(FINFO, "Setting --timeout=%d to match server\n", val);
+			set_io_timeout(val);
+		}
+		break;
+	case MSG_NOOP:
+		/* Support protocol-30 keep-alive method. */
+		if (msg_bytes != 0)
+			goto invalid_msg;
+		iobuf.in_multiplexed = 1;
+		if (am_sender)
+			maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
+		break;
+	case MSG_DELETED:
+		if (msg_bytes >= sizeof data)
+			goto overflow;
+		if (am_generator) {
+			raw_read_buf(data, msg_bytes);
+			iobuf.in_multiplexed = 1;
+			send_msg(MSG_DELETED, data, msg_bytes, 1);
 			break;
-		case MSG_DELETED:
-			if (msg_bytes >= sizeof line)
-				goto overflow;
+		}
 #ifdef ICONV_OPTION
-			if (ic_recv != (iconv_t)-1) {
-				xbuf outbuf, inbuf;
-				char ibuf[512];
-				int add_null = 0;
-
-				INIT_CONST_XBUF(outbuf, line);
-				INIT_XBUF(inbuf, ibuf, 0, -1);
-
-				while (msg_bytes) {
-					inbuf.len = msg_bytes > sizeof ibuf
-						  ? sizeof ibuf : msg_bytes;
-					read_loop(fd, inbuf.buf, inbuf.len);
-					if (!(msg_bytes -= inbuf.len)
-					 && !ibuf[inbuf.len-1])
-						inbuf.len--, add_null = 1;
-					if (iconvbufs(ic_send, &inbuf, &outbuf,
-					    ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE) < 0)
-						goto overflow;
-				}
-				if (add_null) {
-					if (outbuf.len == outbuf.size)
+		if (ic_recv != (iconv_t)-1) {
+			xbuf outbuf, inbuf;
+			char ibuf[512];
+			int add_null = 0;
+			int flags = ICB_INCLUDE_BAD | ICB_INIT;
+
+			INIT_CONST_XBUF(outbuf, data);
+			INIT_XBUF(inbuf, ibuf, 0, (size_t)-1);
+
+			while (msg_bytes) {
+				size_t len = msg_bytes > sizeof ibuf - inbuf.len ? sizeof ibuf - inbuf.len : msg_bytes;
+				raw_read_buf(ibuf + inbuf.len, len);
+				inbuf.pos = 0;
+				inbuf.len += len;
+				if (!(msg_bytes -= len) && !ibuf[inbuf.len-1])
+					inbuf.len--, add_null = 1;
+				if (iconvbufs(ic_send, &inbuf, &outbuf, flags) < 0) {
+					if (errno == E2BIG)
 						goto overflow;
-					outbuf.buf[outbuf.len++] = '\0';
+					/* Buffer ended with an incomplete char, so move the
+					 * bytes to the start of the buffer and continue. */
+					memmove(ibuf, ibuf + inbuf.pos, inbuf.len);
 				}
-				msg_bytes = outbuf.len;
-			} else
-#endif
-				read_loop(fd, line, msg_bytes);
-			/* A directory name was sent with the trailing null */
-			if (msg_bytes > 0 && !line[msg_bytes-1])
-				log_delete(line, S_IFDIR);
-			else {
-				line[msg_bytes] = '\0';
-				log_delete(line, S_IFREG);
+				flags &= ~ICB_INIT;
 			}
-			break;
-		case MSG_SUCCESS:
-			if (msg_bytes != 4) {
-			  invalid_msg:
-				rprintf(FERROR, "invalid multi-message %d:%ld [%s]\n",
-					tag, (long)msg_bytes, who_am_i());
-				exit_cleanup(RERR_STREAMIO);
+			if (add_null) {
+				if (outbuf.len == outbuf.size)
+					goto overflow;
+				outbuf.buf[outbuf.len++] = '\0';
 			}
-			read_loop(fd, line, msg_bytes);
-			successful_send(IVAL(line, 0));
-			break;
-		case MSG_NO_SEND:
-			if (msg_bytes != 4)
-				goto invalid_msg;
-			read_loop(fd, line, msg_bytes);
-			send_msg_int(MSG_NO_SEND, IVAL(line, 0));
-			break;
-		case MSG_INFO:
-		case MSG_ERROR:
-		case MSG_ERROR_XFER:
-		case MSG_WARNING:
-			if (msg_bytes >= sizeof line) {
-			    overflow:
-				rprintf(FERROR,
-					"multiplexing overflow %d:%ld [%s]\n",
-					tag, (long)msg_bytes, who_am_i());
-				exit_cleanup(RERR_STREAMIO);
+			msg_bytes = outbuf.len;
+		} else
+#endif
+			raw_read_buf(data, msg_bytes);
+		iobuf.in_multiplexed = 1;
+		/* A directory name was sent with the trailing null */
+		if (msg_bytes > 0 && !data[msg_bytes-1])
+			log_delete(data, S_IFDIR);
+		else {
+			data[msg_bytes] = '\0';
+			log_delete(data, S_IFREG);
+		}
+		break;
+	case MSG_SUCCESS:
+		if (msg_bytes != 4) {
+		  invalid_msg:
+			rprintf(FERROR, "invalid multi-message %d:%lu [%s%s]\n",
+				tag, (unsigned long)msg_bytes, who_am_i(),
+				inc_recurse ? "/inc" : "");
+			exit_cleanup(RERR_STREAMIO);
+		}
+		val = raw_read_int();
+		iobuf.in_multiplexed = 1;
+		if (am_generator)
+			got_flist_entry_status(FES_SUCCESS, val);
+		else
+			successful_send(val);
+		break;
+	case MSG_NO_SEND:
+		if (msg_bytes != 4)
+			goto invalid_msg;
+		val = raw_read_int();
+		iobuf.in_multiplexed = 1;
+		if (am_generator)
+			got_flist_entry_status(FES_NO_SEND, val);
+		else
+			send_msg_int(MSG_NO_SEND, val);
+		break;
+	case MSG_ERROR_SOCKET:
+	case MSG_ERROR_UTF8:
+	case MSG_CLIENT:
+	case MSG_LOG:
+		if (!am_generator)
+			goto invalid_msg;
+		if (tag == MSG_ERROR_SOCKET)
+			msgs2stderr = 1;
+		/* FALL THROUGH */
+	case MSG_INFO:
+	case MSG_ERROR:
+	case MSG_ERROR_XFER:
+	case MSG_WARNING:
+		if (msg_bytes >= sizeof data) {
+		    overflow:
+			rprintf(FERROR,
+				"multiplexing overflow %d:%lu [%s%s]\n",
+				tag, (unsigned long)msg_bytes, who_am_i(),
+				inc_recurse ? "/inc" : "");
+			exit_cleanup(RERR_STREAMIO);
+		}
+		raw_read_buf(data, msg_bytes);
+		/* We don't set in_multiplexed value back to 1 before writing this message
+		 * because the write might loop back and read yet another message, over and
+		 * over again, while waiting for room to put the message in the msg buffer. */
+		rwrite((enum logcode)tag, data, msg_bytes, !am_generator);
+		iobuf.in_multiplexed = 1;
+		if (first_message) {
+			if (list_only && !am_sender && tag == 1 && msg_bytes < sizeof data) {
+				data[msg_bytes] = '\0';
+				check_for_d_option_error(data);
+			}
+			first_message = 0;
+		}
+		break;
+	case MSG_ERROR_EXIT:
+		if (msg_bytes == 4)
+			val = raw_read_int();
+		else if (msg_bytes == 0)
+			val = 0;
+		else
+			goto invalid_msg;
+		iobuf.in_multiplexed = 1;
+		if (DEBUG_GTE(EXIT, 3))
+			rprintf(FINFO, "[%s] got MSG_ERROR_EXIT with %ld bytes\n", who_am_i(), (long)msg_bytes);
+		if (msg_bytes == 0) {
+			if (!am_sender && !am_generator) {
+				if (DEBUG_GTE(EXIT, 3)) {
+					rprintf(FINFO, "[%s] sending MSG_ERROR_EXIT (len 0)\n",
+						who_am_i());
+				}
+				send_msg(MSG_ERROR_EXIT, "", 0, 0);
+				io_flush(FULL_FLUSH);
 			}
-			read_loop(fd, line, msg_bytes);
-			rwrite((enum logcode)tag, line, msg_bytes, 1);
-			if (first_message) {
-				if (list_only && !am_sender && tag == 1) {
-					line[msg_bytes] = '\0';
-					check_for_d_option_error(line);
+		} else if (protocol_version >= 31) {
+			if (am_generator || am_receiver) {
+				if (DEBUG_GTE(EXIT, 3)) {
+					rprintf(FINFO, "[%s] sending MSG_ERROR_EXIT with exit_code %d\n",
+						who_am_i(), val);
 				}
-				first_message = 0;
+				send_msg_int(MSG_ERROR_EXIT, val);
+			} else {
+				if (DEBUG_GTE(EXIT, 3)) {
+					rprintf(FINFO, "[%s] sending MSG_ERROR_EXIT (len 0)\n",
+						who_am_i());
+				}
+				send_msg(MSG_ERROR_EXIT, "", 0, 0);
 			}
-			break;
-		default:
-			rprintf(FERROR, "unexpected tag %d [%s]\n",
-				tag, who_am_i());
-			exit_cleanup(RERR_STREAMIO);
 		}
+		/* Send a negative linenum so that we don't end up
+		 * with a duplicate exit message. */
+		_exit_cleanup(val, __FILE__, 0 - __LINE__);
+	default:
+		rprintf(FERROR, "unexpected tag %d [%s%s]\n",
+			tag, who_am_i(), inc_recurse ? "/inc" : "");
+		exit_cleanup(RERR_STREAMIO);
 	}
 
-	if (iobuf_in_remaining == 0)
-		io_flush(NORMAL_FLUSH);
-
-	return cnt;
+	assert(iobuf.in_multiplexed > 0);
 }
 
-/* Do a buffered read from fd.  Don't return until all N bytes have
- * been read.  If all N can't be read then exit with an error. */
-static void readfd(int fd, char *buffer, size_t N)
+static void drain_multiplex_messages(void)
 {
-	int  cnt;
-	size_t total = 0;
-
-	while (total < N) {
-		cnt = readfd_unbuffered(fd, buffer + total, N-total);
-		total += cnt;
-	}
-
-	if (fd == write_batch_monitor_in) {
-		if ((size_t)write(batch_fd, buffer, total) != total)
-			exit_cleanup(RERR_FILEIO);
+	while (IN_MULTIPLEXED_AND_READY && iobuf.in.len) {
+		if (iobuf.raw_input_ends_before) {
+			size_t raw_len = iobuf.raw_input_ends_before - iobuf.in.pos;
+			iobuf.raw_input_ends_before = 0;
+			if (raw_len >= iobuf.in.len) {
+				iobuf.in.len = 0;
+				break;
+			}
+			iobuf.in.len -= raw_len;
+			if ((iobuf.in.pos += raw_len) >= iobuf.in.size)
+				iobuf.in.pos -= iobuf.in.size;
+		}
+		read_a_msg();
 	}
+}
 
-	if (fd == flist_forward_from)
-		writefd(iobuf_f_out, buffer, total);
+void wait_for_receiver(void)
+{
+	if (!iobuf.raw_input_ends_before)
+		read_a_msg();
 
-	if (fd == sock_f_in)
-		stats.total_read += total;
+	if (iobuf.raw_input_ends_before) {
+		int ndx = read_int(iobuf.in_fd);
+		if (ndx < 0) {
+			switch (ndx) {
+			case NDX_FLIST_EOF:
+				flist_eof = 1;
+				if (DEBUG_GTE(FLIST, 3))
+					rprintf(FINFO, "[%s] flist_eof=1\n", who_am_i());
+				break;
+			case NDX_DONE:
+				msgdone_cnt++;
+				break;
+			default:
+				exit_cleanup(RERR_STREAMIO);
+			}
+		} else {
+			struct file_list *flist;
+			flist_receiving_enabled = False;
+			if (DEBUG_GTE(FLIST, 2)) {
+				rprintf(FINFO, "[%s] receiving flist for dir %d\n",
+					who_am_i(), ndx);
+			}
+			flist = recv_file_list(iobuf.in_fd);
+			flist->parent_ndx = ndx;
+#ifdef SUPPORT_HARD_LINKS
+			if (preserve_hard_links)
+				match_hard_links(flist);
+#endif
+			flist_receiving_enabled = True;
+		}
+	}
 }
 
 unsigned short read_shortint(int f)
 {
 	char b[2];
-	readfd(f, b, 2);
+	read_buf(f, b, 2);
 	return (UVAL(b, 1) << 8) + UVAL(b, 0);
 }
 
 int32 read_int(int f)
 {
 	char b[4];
 	int32 num;
 
-	readfd(f, b, 4);
+	read_buf(f, b, 4);
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
-	    char b[5];
-	    int32 x;
+		char b[5];
+		int32 x;
 	} u;
 	uchar ch;
 	int extra;
 
 	u.x = 0;
-	readfd(f, (char*)&ch, 1);
+	ch = read_byte(f);
 	extra = int_byte_extra[ch / 4];
 	if (extra) {
 		uchar bit = ((uchar)1<<(8-extra));
 		if (extra >= (int)sizeof u.b) {
 			rprintf(FERROR, "Overflow in read_varint()\n");
 			exit_cleanup(RERR_STREAMIO);
 		}
-		readfd(f, u.b, extra);
+		read_buf(f, u.b, extra);
 		u.b[extra] = ch & (bit-1);
 	} else
 		u.b[0] = ch;
 #if CAREFUL_ALIGNMENT
 	u.x = IVAL(u.b,0);
 #endif
