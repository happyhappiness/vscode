 {
 	packet_trace("0000", 4, 1);
 	strbuf_add(buf, "0000", 4);
 }
 
 #define hex(a) (hexchar[(a) & 15])
-static char buffer[1000];
-static unsigned format_packet(const char *fmt, va_list args)
+static void format_packet(struct strbuf *out, const char *fmt, va_list args)
 {
 	static char hexchar[] = "0123456789abcdef";
-	unsigned n;
+	size_t orig_len, n;
 
-	n = vsnprintf(buffer + 4, sizeof(buffer) - 4, fmt, args);
-	if (n >= sizeof(buffer)-4)
+	orig_len = out->len;
+	strbuf_addstr(out, "0000");
+	strbuf_vaddf(out, fmt, args);
+	n = out->len - orig_len;
+
+	if (n > LARGE_PACKET_MAX)
 		die("protocol error: impossibly long line");
-	n += 4;
-	buffer[0] = hex(n >> 12);
-	buffer[1] = hex(n >> 8);
-	buffer[2] = hex(n >> 4);
-	buffer[3] = hex(n);
-	packet_trace(buffer+4, n-4, 1);
-	return n;
+
+	out->buf[orig_len + 0] = hex(n >> 12);
+	out->buf[orig_len + 1] = hex(n >> 8);
+	out->buf[orig_len + 2] = hex(n >> 4);
+	out->buf[orig_len + 3] = hex(n);
+	packet_trace(out->buf + orig_len + 4, n - 4, 1);
 }
 
 void packet_write(int fd, const char *fmt, ...)
 {
+	static struct strbuf buf = STRBUF_INIT;
 	va_list args;
-	unsigned n;
 
+	strbuf_reset(&buf);
 	va_start(args, fmt);
-	n = format_packet(fmt, args);
+	format_packet(&buf, fmt, args);
 	va_end(args);
-	write_or_die(fd, buffer, n);
+	write_or_die(fd, buf.buf, buf.len);
 }
 
 void packet_buf_write(struct strbuf *buf, const char *fmt, ...)
 {
 	va_list args;
-	unsigned n;
 
 	va_start(args, fmt);
-	n = format_packet(fmt, args);
+	format_packet(buf, fmt, args);
 	va_end(args);
-	strbuf_add(buf, buffer, n);
 }
 
 static int get_packet_data(int fd, char **src_buf, size_t *src_size,
 			   void *dst, unsigned size, int options)
 {
 	ssize_t ret;
