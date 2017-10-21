 			FD_ZERO(&e_fds);
 			FD_SET(fd, &e_fds);
 			tv.tv_sec = select_timeout;
 			tv.tv_usec = 0;
 			if (!select(fd+1, &r_fds, NULL, &e_fds, &tv))
 				check_timeout();
-			if (FD_ISSET(fd, &e_fds)) {
-				rsyserr(FINFO, errno,
-					"select exception on fd %d", fd);
-			}
+			/*if (FD_ISSET(fd, &e_fds))
+				rprintf(FINFO, "select exception on fd %d\n", fd); */
 			continue;
 		}
 		if (cnt != 1)
 			break;
-		if (nulls? !ch : (ch == '\r' || ch == '\n')) {
-			/* Skip empty lines if reading locally. */
-			if (!reading_remotely && s == fname)
+		if (flags & RL_EOL_NULLS ? ch == '\0' : (ch == '\r' || ch == '\n')) {
+			/* Skip empty lines if dumping comments. */
+			if (flags & RL_DUMP_COMMENTS && s == buf)
 				continue;
 			break;
 		}
 		if (s < eob)
 			*s++ = ch;
 	}
 	*s = '\0';
 
-	/* Dump comments. */
-	if (*fname == '#' || *fname == ';')
+	if (flags & RL_DUMP_COMMENTS && (*buf == '#' || *buf == ';'))
 		goto start;
 
-	return s - fname;
+#ifdef ICONV_OPTION
+	if (flags & RL_CONVERT) {
+		xbuf outbuf;
+		INIT_XBUF(outbuf, buf, 0, bufsiz);
+		iconv_buf.pos = 0;
+		iconv_buf.len = s - iconv_buf.buf;
+		iconvbufs(ic_recv, &iconv_buf, &outbuf,
+			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
+		outbuf.buf[outbuf.len] = '\0';
+		return outbuf.len;
+	}
+#endif
+
+	return s - buf;
 }
 
-static char *iobuf_out;
-static int iobuf_out_cnt;
+int read_args(int f_in, char *mod_name, char *buf, size_t bufsiz, int rl_nulls,
+	      char ***argv_p, int *argc_p, char **request_p)
+{
+	int maxargs = MAX_ARGS;
+	int dot_pos = 0;
+	int argc = 0;
+	char **argv, *p;
+	int rl_flags = (rl_nulls ? RL_EOL_NULLS : 0);
 
-void io_start_buffering_out(void)
+#ifdef ICONV_OPTION
+	rl_flags |= (protect_args && ic_recv != (iconv_t)-1 ? RL_CONVERT : 0);
+#endif
+
+	if (!(argv = new_array(char *, maxargs)))
+		out_of_memory("read_args");
+	if (mod_name)
+		argv[argc++] = "rsyncd";
+
+	while (1) {
+		if (read_line(f_in, buf, bufsiz, rl_flags) == 0)
+			break;
+
+		if (argc == maxargs) {
+			maxargs += MAX_ARGS;
+			if (!(argv = realloc_array(argv, char *, maxargs)))
+				out_of_memory("read_args");
+		}
+
+		if (dot_pos) {
+			if (request_p) {
+				*request_p = strdup(buf);
+				request_p = NULL;
+			}
+			if (mod_name)
+				glob_expand_module(mod_name, buf, &argv, &argc, &maxargs);
+			else
+				glob_expand(buf, &argv, &argc, &maxargs);
+		} else {
+			if (!(p = strdup(buf)))
+				out_of_memory("read_args");
+			argv[argc++] = p;
+			if (*p == '.' && p[1] == '\0')
+				dot_pos = argc;
+		}
+	}
+
+	*argc_p = argc;
+	*argv_p = argv;
+
+	return dot_pos ? dot_pos : argc;
+}
+
+int io_start_buffering_out(int f_out)
 {
-	if (iobuf_out)
-		return;
+	if (iobuf_out) {
+		assert(f_out == iobuf_f_out);
+		return 0;
+	}
 	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
 		out_of_memory("io_start_buffering_out");
 	iobuf_out_cnt = 0;
+	iobuf_f_out = f_out;
+	return 1;
 }
 
-static char *iobuf_in;
-static size_t iobuf_in_siz;
-
-void io_start_buffering_in(void)
+int io_start_buffering_in(int f_in)
 {
-	if (iobuf_in)
-		return;
+	if (iobuf_in) {
+		assert(f_in == iobuf_f_in);
+		return 0;
+	}
 	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
 	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
 		out_of_memory("io_start_buffering_in");
+	iobuf_f_in = f_in;
+	return 1;
 }
 
-void io_end_buffering(void)
+void io_end_buffering_in(void)
 {
-	io_flush(NORMAL_FLUSH);
-	if (!io_multiplexing_out) {
-		free(iobuf_out);
-		iobuf_out = NULL;
-	}
+	if (!iobuf_in)
+		return;
+	free(iobuf_in);
+	iobuf_in = NULL;
+	iobuf_in_ndx = 0;
+	iobuf_in_remaining = 0;
+	iobuf_f_in = -1;
+}
+
+void io_end_buffering_out(void)
+{
+	if (!iobuf_out)
+		return;
+	io_flush(FULL_FLUSH);
+	free(iobuf_out);
+	iobuf_out = NULL;
+	iobuf_f_out = -1;
 }
 
-void maybe_flush_socket(void)
+void maybe_flush_socket(int important)
 {
-	if (iobuf_out && iobuf_out_cnt && time(NULL) - last_io_out >= 5)
+	if (iobuf_out && iobuf_out_cnt
+	 && (important || time(NULL) - last_io_out >= 5))
 		io_flush(NORMAL_FLUSH);
 }
 
 void maybe_send_keepalive(void)
 {
 	if (time(NULL) - last_io_out >= allowed_lull) {
 		if (!iobuf_out || !iobuf_out_cnt) {
 			if (protocol_version < 29)
 				return; /* there's nothing we can do */
-			write_int(sock_f_out, the_file_list->count);
-			write_shortint(sock_f_out, ITEM_IS_NEW);
+			if (protocol_version >= 30)
+				send_msg(MSG_NOOP, "", 0, 0);
+			else {
+				write_int(sock_f_out, cur_flist->used);
+				write_shortint(sock_f_out, ITEM_IS_NEW);
+			}
 		}
 		if (iobuf_out)
 			io_flush(NORMAL_FLUSH);
 	}
 }
 
+void start_flist_forward(int f_in)
+{
+	assert(iobuf_out != NULL);
+	assert(iobuf_f_out == msg_fd_out);
+	flist_forward_from = f_in;
+}
+
+void stop_flist_forward()
+{
+	flist_forward_from = -1;
+	io_flush(FULL_FLUSH);
+}
+
 /**
  * Continue trying to read len bytes - don't return until len has been
  * read.
  **/
 static void read_loop(int fd, char *buf, size_t len)
 {
