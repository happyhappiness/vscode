 
 	writefd(f, (char*)lenbuf, lb - lenbuf + 1);
 	if (len)
 		writefd(f, str, len);
 }
 
-/**
- * Read a line of up to @p maxlen characters into @p buf (not counting
- * the trailing null).  Strips the (required) trailing newline and all
- * carriage returns.
- *
- * @return 1 for success; 0 for I/O error or truncation.
- **/
-int read_line(int f, char *buf, size_t maxlen)
+/* Send a file-list index using a byte-reduction method. */
+void write_ndx(int f, int32 ndx)
+{
+	static int32 prev_positive = -1, prev_negative = 1;
+	int32 diff, cnt = 0;
+	char b[6];
+
+	if (protocol_version < 30 || read_batch) {
+		write_int(f, ndx);
+		return;
+	}
+
+	/* Send NDX_DONE as a single-byte 0 with no side effects.  Send
+	 * negative nums as a positive after sending a leading 0xFF. */
+	if (ndx >= 0) {
+		diff = ndx - prev_positive;
+		prev_positive = ndx;
+	} else if (ndx == NDX_DONE) {
+		*b = 0;
+		writefd(f, b, 1);
+		return;
+	} else {
+		b[cnt++] = (char)0xFF;
+		ndx = -ndx;
+		diff = ndx - prev_negative;
+		prev_negative = ndx;
+	}
+
+	/* A diff of 1 - 253 is sent as a one-byte diff; a diff of 254 - 32767
+	 * or 0 is sent as a 0xFE + a two-byte diff; otherwise we send 0xFE
+	 * & all 4 bytes of the (non-negative) num with the high-bit set. */
+	if (diff < 0xFE && diff > 0)
+		b[cnt++] = (char)diff;
+	else if (diff < 0 || diff > 0x7FFF) {
+		b[cnt++] = (char)0xFE;
+		b[cnt++] = (char)((ndx >> 24) | 0x80);
+		b[cnt++] = (char)ndx;
+		b[cnt++] = (char)(ndx >> 8);
+		b[cnt++] = (char)(ndx >> 16);
+	} else {
+		b[cnt++] = (char)0xFE;
+		b[cnt++] = (char)(diff >> 8);
+		b[cnt++] = (char)diff;
+	}
+	writefd(f, b, cnt);
+}
+
+/* Receive a file-list index using a byte-reduction method. */
+int32 read_ndx(int f)
+{
+	static int32 prev_positive = -1, prev_negative = 1;
+	int32 *prev_ptr, num;
+	char b[4];
+
+	if (protocol_version < 30)
+		return read_int(f);
+
+	readfd(f, b, 1);
+	if (CVAL(b, 0) == 0xFF) {
+		readfd(f, b, 1);
+		prev_ptr = &prev_negative;
+	} else if (CVAL(b, 0) == 0)
+		return NDX_DONE;
+	else
+		prev_ptr = &prev_positive;
+	if (CVAL(b, 0) == 0xFE) {
+		readfd(f, b, 2);
+		if (CVAL(b, 0) & 0x80) {
+			b[3] = CVAL(b, 0) & ~0x80;
+			b[0] = b[1];
+			readfd(f, b+1, 2);
+			num = IVAL(b, 0);
+		} else
+			num = (UVAL(b,0)<<8) + UVAL(b,1) + *prev_ptr;
+	} else
+		num = UVAL(b, 0) + *prev_ptr;
+	*prev_ptr = num;
+	if (prev_ptr == &prev_negative)
+		num = -num;
+	return num;
+}
+
+/* Read a line of up to bufsiz-1 characters into buf.  Strips
+ * the (required) trailing newline and all carriage returns.
+ * Returns 1 for success; 0 for I/O error or truncation. */
+int read_line_old(int f, char *buf, size_t bufsiz)
 {
-	while (maxlen) {
+	bufsiz--; /* leave room for the null */
+	while (bufsiz > 0) {
 		buf[0] = 0;
 		read_buf(f, buf, 1);
 		if (buf[0] == 0)
 			return 0;
 		if (buf[0] == '\n')
 			break;
 		if (buf[0] != '\r') {
 			buf++;
-			maxlen--;
+			bufsiz--;
 		}
 	}
 	*buf = '\0';
-	return maxlen > 0;
+	return bufsiz > 0;
 }
 
 void io_printf(int fd, const char *format, ...)
 {
 	va_list ap;
 	char buf[BIGPATHBUFLEN];
