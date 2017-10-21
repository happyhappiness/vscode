 
 	va_start(ap, format);
 	len = vsnprintf(buf, sizeof buf, format, ap);
 	va_end(ap);
 
 	if (len < 0)
-		exit_cleanup(RERR_STREAMIO);
+		exit_cleanup(RERR_PROTOCOL);
 
 	if (len > (int)sizeof buf) {
 		rprintf(FERROR, "io_printf() was too long for the buffer.\n");
-		exit_cleanup(RERR_STREAMIO);
+		exit_cleanup(RERR_PROTOCOL);
 	}
 
 	write_sbuf(fd, buf);
 }
 
-/** Setup for multiplexing a MSG_* stream with the data stream. */
-void io_start_multiplex_out(void)
+/* Setup for multiplexing a MSG_* stream with the data stream. */
+void io_start_multiplex_out(int fd)
 {
-	io_flush(NORMAL_FLUSH);
-	io_start_buffering_out(sock_f_out);
-	io_multiplexing_out = 1;
-}
+	io_flush(FULL_FLUSH);
 
-/** Setup for multiplexing a MSG_* stream with the data stream. */
-void io_start_multiplex_in(void)
-{
-	io_flush(NORMAL_FLUSH);
-	io_start_buffering_in(sock_f_in);
-	io_multiplexing_in = 1;
+	if (msgs2stderr && DEBUG_GTE(IO, 2))
+		rprintf(FINFO, "[%s] io_start_multiplex_out(%d)\n", who_am_i(), fd);
+
+	if (!iobuf.msg.buf)
+		alloc_xbuf(&iobuf.msg, ROUND_UP_1024(IO_BUFFER_SIZE));
+
+	iobuf.out_empty_len = 4; /* See also OUT_MULTIPLEXED */
+	io_start_buffering_out(fd);
+	got_kill_signal = 0;
+
+	iobuf.raw_data_header_pos = iobuf.out.pos + iobuf.out.len;
+	iobuf.out.len += 4;
 }
 
-/** Write an message to the multiplexed data stream. */
-int io_multiplex_write(enum msgcode code, const char *buf, size_t len, int convert)
+/* Setup for multiplexing a MSG_* stream with the data stream. */
+void io_start_multiplex_in(int fd)
 {
-	if (!io_multiplexing_out)
-		return 0;
-	io_flush(NORMAL_FLUSH);
-	stats.total_written += (len+4);
-	mplex_write(sock_f_out, code, buf, len, convert);
-	return 1;
+	if (msgs2stderr && DEBUG_GTE(IO, 2))
+		rprintf(FINFO, "[%s] io_start_multiplex_in(%d)\n", who_am_i(), fd);
+
+	iobuf.in_multiplexed = 1; /* See also IN_MULTIPLEXED */
+	io_start_buffering_in(fd);
 }
 
-void io_end_multiplex_in(void)
+int io_end_multiplex_in(int mode)
 {
-	io_multiplexing_in = 0;
-	io_end_buffering_in();
+	int ret = iobuf.in_multiplexed ? iobuf.in_fd : -1;
+
+	if (msgs2stderr && DEBUG_GTE(IO, 2))
+		rprintf(FINFO, "[%s] io_end_multiplex_in(mode=%d)\n", who_am_i(), mode);
+
+	iobuf.in_multiplexed = 0;
+	if (mode == MPLX_SWITCHING)
+		iobuf.raw_input_ends_before = 0;
+	else
+		assert(iobuf.raw_input_ends_before == 0);
+	if (mode != MPLX_TO_BUFFERED)
+		io_end_buffering_in(mode);
+
+	return ret;
 }
 
-/** Stop output multiplexing. */
-void io_end_multiplex_out(void)
+int io_end_multiplex_out(int mode)
 {
-	io_multiplexing_out = 0;
-	io_end_buffering_out();
+	int ret = iobuf.out_empty_len ? iobuf.out_fd : -1;
+
+	if (msgs2stderr && DEBUG_GTE(IO, 2))
+		rprintf(FINFO, "[%s] io_end_multiplex_out(mode=%d)\n", who_am_i(), mode);
+
+	if (mode != MPLX_TO_BUFFERED)
+		io_end_buffering_out(mode);
+	else
+		io_flush(FULL_FLUSH);
+
+	iobuf.out.len = 0;
+	iobuf.out_empty_len = 0;
+	if (got_kill_signal > 0) /* Just in case... */
+		handle_kill_signal(False);
+	got_kill_signal = -1;
+
+	return ret;
 }
 
 void start_write_batch(int fd)
 {
 	/* Some communication has already taken place, but we don't
 	 * enable batch writing until here so that we can write a
