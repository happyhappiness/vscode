 void packet_flush(int fd)
 {
 	packet_trace("0000", 4, 1);
 	write_or_die(fd, "0000", 4);
 }
 
+int packet_flush_gently(int fd)
+{
+	packet_trace("0000", 4, 1);
+	if (write_in_full(fd, "0000", 4) == 4)
+		return 0;
+	return error("flush packet write failed");
+}
+
 void packet_buf_flush(struct strbuf *buf)
 {
 	packet_trace("0000", 4, 1);
 	strbuf_add(buf, "0000", 4);
 }
 
-#define hex(a) (hexchar[(a) & 15])
-static void format_packet(struct strbuf *out, const char *fmt, va_list args)
+static void set_packet_header(char *buf, const int size)
 {
 	static char hexchar[] = "0123456789abcdef";
+
+	#define hex(a) (hexchar[(a) & 15])
+	buf[0] = hex(size >> 12);
+	buf[1] = hex(size >> 8);
+	buf[2] = hex(size >> 4);
+	buf[3] = hex(size);
+	#undef hex
+}
+
+static void format_packet(struct strbuf *out, const char *fmt, va_list args)
+{
 	size_t orig_len, n;
 
 	orig_len = out->len;
 	strbuf_addstr(out, "0000");
 	strbuf_vaddf(out, fmt, args);
 	n = out->len - orig_len;
 
 	if (n > LARGE_PACKET_MAX)
 		die("protocol error: impossibly long line");
 
-	out->buf[orig_len + 0] = hex(n >> 12);
-	out->buf[orig_len + 1] = hex(n >> 8);
-	out->buf[orig_len + 2] = hex(n >> 4);
-	out->buf[orig_len + 3] = hex(n);
+	set_packet_header(&out->buf[orig_len], n);
 	packet_trace(out->buf + orig_len + 4, n - 4, 1);
 }
 
-void packet_write(int fd, const char *fmt, ...)
+static int packet_write_fmt_1(int fd, int gently,
+			      const char *fmt, va_list args)
+{
+	struct strbuf buf = STRBUF_INIT;
+	ssize_t count;
+
+	format_packet(&buf, fmt, args);
+	count = write_in_full(fd, buf.buf, buf.len);
+	if (count == buf.len)
+		return 0;
+
+	if (!gently) {
+		check_pipe(errno);
+		die_errno("packet write with format failed");
+	}
+	return error("packet write with format failed");
+}
+
+void packet_write_fmt(int fd, const char *fmt, ...)
 {
-	static struct strbuf buf = STRBUF_INIT;
 	va_list args;
 
-	strbuf_reset(&buf);
 	va_start(args, fmt);
-	format_packet(&buf, fmt, args);
+	packet_write_fmt_1(fd, 0, fmt, args);
+	va_end(args);
+}
+
+int packet_write_fmt_gently(int fd, const char *fmt, ...)
+{
+	int status;
+	va_list args;
+
+	va_start(args, fmt);
+	status = packet_write_fmt_1(fd, 1, fmt, args);
 	va_end(args);
-	write_or_die(fd, buf.buf, buf.len);
+	return status;
+}
+
+static int packet_write_gently(const int fd_out, const char *buf, size_t size)
+{
+	static char packet_write_buffer[LARGE_PACKET_MAX];
+	size_t packet_size;
+
+	if (size > sizeof(packet_write_buffer) - 4)
+		return error("packet write failed - data exceeds max packet size");
+
+	packet_trace(buf, size, 1);
+	packet_size = size + 4;
+	set_packet_header(packet_write_buffer, packet_size);
+	memcpy(packet_write_buffer + 4, buf, size);
+	if (write_in_full(fd_out, packet_write_buffer, packet_size) == packet_size)
+		return 0;
+	return error("packet write failed");
 }
 
 void packet_buf_write(struct strbuf *buf, const char *fmt, ...)
 {
 	va_list args;
 
 	va_start(args, fmt);
 	format_packet(buf, fmt, args);
 	va_end(args);
 }
 
+int write_packetized_from_fd(int fd_in, int fd_out)
+{
+	static char buf[LARGE_PACKET_DATA_MAX];
+	int err = 0;
+	ssize_t bytes_to_write;
+
+	while (!err) {
+		bytes_to_write = xread(fd_in, buf, sizeof(buf));
+		if (bytes_to_write < 0)
+			return COPY_READ_ERROR;
+		if (bytes_to_write == 0)
+			break;
+		err = packet_write_gently(fd_out, buf, bytes_to_write);
+	}
+	if (!err)
+		err = packet_flush_gently(fd_out);
+	return err;
+}
+
+int write_packetized_from_buf(const char *src_in, size_t len, int fd_out)
+{
+	int err = 0;
+	size_t bytes_written = 0;
+	size_t bytes_to_write;
+
+	while (!err) {
+		if ((len - bytes_written) > LARGE_PACKET_DATA_MAX)
+			bytes_to_write = LARGE_PACKET_DATA_MAX;
+		else
+			bytes_to_write = len - bytes_written;
+		if (bytes_to_write == 0)
+			break;
+		err = packet_write_gently(fd_out, src_in + bytes_written, bytes_to_write);
+		bytes_written += bytes_to_write;
+	}
+	if (!err)
+		err = packet_flush_gently(fd_out);
+	return err;
+}
+
 static int get_packet_data(int fd, char **src_buf, size_t *src_size,
 			   void *dst, unsigned size, int options)
 {
 	ssize_t ret;
 
 	if (fd >= 0 && src_buf && *src_buf)
