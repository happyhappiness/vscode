  * primary payload.  Things coming over band #2 is not necessarily
  * error; they are usually informative message on the standard error
  * stream, aka "verbose").  A message over band #3 is a signal that
  * the remote died unexpectedly.  A flush() concludes the stream.
  */
 
-#define PREFIX "remote:"
+#define PREFIX "remote: "
 
 #define ANSI_SUFFIX "\033[K"
 #define DUMB_SUFFIX "        "
 
-#define FIX_SIZE 10  /* large enough for any of the above */
-
 int recv_sideband(const char *me, int in_stream, int out)
 {
-	unsigned pf = strlen(PREFIX);
-	unsigned sf;
-	char buf[LARGE_PACKET_MAX + 2*FIX_SIZE];
-	char *suffix, *term;
-	int skip_pf = 0;
+	const char *term, *suffix;
+	char buf[LARGE_PACKET_MAX + 1];
+	struct strbuf outbuf = STRBUF_INIT;
+	int retval = 0;
 
-	memcpy(buf, PREFIX, pf);
 	term = getenv("TERM");
 	if (isatty(2) && term && strcmp(term, "dumb"))
 		suffix = ANSI_SUFFIX;
 	else
 		suffix = DUMB_SUFFIX;
-	sf = strlen(suffix);
 
-	while (1) {
+	while (!retval) {
+		const char *b, *brk;
 		int band, len;
-		len = packet_read(in_stream, NULL, NULL, buf + pf, LARGE_PACKET_MAX, 0);
+		len = packet_read(in_stream, NULL, NULL, buf, LARGE_PACKET_MAX, 0);
 		if (len == 0)
 			break;
 		if (len < 1) {
-			fprintf(stderr, "%s: protocol error: no band designator\n", me);
-			return SIDEBAND_PROTOCOL_ERROR;
+			strbuf_addf(&outbuf,
+				    "%s%s: protocol error: no band designator",
+				    outbuf.len ? "\n" : "", me);
+			retval = SIDEBAND_PROTOCOL_ERROR;
+			break;
 		}
-		band = buf[pf] & 0xff;
+		band = buf[0] & 0xff;
+		buf[len] = '\0';
 		len--;
 		switch (band) {
 		case 3:
-			buf[pf] = ' ';
-			buf[pf+1+len] = '\0';
-			fprintf(stderr, "%s\n", buf);
-			return SIDEBAND_REMOTE_ERROR;
+			strbuf_addf(&outbuf, "%s%s%s", outbuf.len ? "\n" : "",
+				    PREFIX, buf + 1);
+			retval = SIDEBAND_REMOTE_ERROR;
+			break;
 		case 2:
-			buf[pf] = ' ';
-			do {
-				char *b = buf;
-				int brk = 0;
-
-				/*
-				 * If the last buffer didn't end with a line
-				 * break then we should not print a prefix
-				 * this time around.
-				 */
-				if (skip_pf) {
-					b += pf+1;
-				} else {
-					len += pf+1;
-					brk += pf+1;
-				}
-
-				/* Look for a line break. */
-				for (;;) {
-					brk++;
-					if (brk > len) {
-						brk = 0;
-						break;
-					}
-					if (b[brk-1] == '\n' ||
-					    b[brk-1] == '\r')
-						break;
-				}
+			b = buf + 1;
 
-				/*
-				 * Let's insert a suffix to clear the end
-				 * of the screen line if a line break was
-				 * found.  Also, if we don't skip the
-				 * prefix, then a non-empty string must be
-				 * present too.
-				 */
-				if (brk > (skip_pf ? 0 : (pf+1 + 1))) {
-					char save[FIX_SIZE];
-					memcpy(save, b + brk, sf);
-					b[brk + sf - 1] = b[brk - 1];
-					memcpy(b + brk - 1, suffix, sf);
-					fprintf(stderr, "%.*s", brk + sf, b);
-					memcpy(b + brk, save, sf);
-					len -= brk;
+			/*
+			 * Append a suffix to each nonempty line to clear the
+			 * end of the screen line.
+			 *
+			 * The output is accumulated in a buffer and
+			 * each line is printed to stderr using
+			 * write(2) to ensure inter-process atomicity.
+			 */
+			while ((brk = strpbrk(b, "\n\r"))) {
+				int linelen = brk - b;
+
+				if (!outbuf.len)
+					strbuf_addstr(&outbuf, PREFIX);
+				if (linelen > 0) {
+					strbuf_addf(&outbuf, "%.*s%s%c",
+						    linelen, b, suffix, *brk);
 				} else {
-					int l = brk ? brk : len;
-					fprintf(stderr, "%.*s", l, b);
-					len -= l;
+					strbuf_addch(&outbuf, *brk);
 				}
+				xwrite(2, outbuf.buf, outbuf.len);
+				strbuf_reset(&outbuf);
 
-				skip_pf = !brk;
-				memmove(buf + pf+1, b + brk, len);
-			} while (len);
-			continue;
+				b = brk + 1;
+			}
+
+			if (*b)
+				strbuf_addf(&outbuf, "%s%s",
+					    outbuf.len ? "" : PREFIX, b);
+			break;
 		case 1:
-			write_or_die(out, buf + pf+1, len);
-			continue;
+			write_or_die(out, buf + 1, len);
+			break;
 		default:
-			fprintf(stderr, "%s: protocol error: bad band #%d\n",
-				me, band);
-			return SIDEBAND_PROTOCOL_ERROR;
+			strbuf_addf(&outbuf, "%s%s: protocol error: bad band #%d",
+				    outbuf.len ? "\n" : "", me, band);
+			retval = SIDEBAND_PROTOCOL_ERROR;
+			break;
 		}
 	}
-	return 0;
+
+	if (outbuf.len) {
+		strbuf_addch(&outbuf, '\n');
+		xwrite(2, outbuf.buf, outbuf.len);
+	}
+	strbuf_release(&outbuf);
+	return retval;
 }
 
 /*
  * fd is connected to the remote side; send the sideband data
  * over multiplexed packet stream.
  */
-ssize_t send_sideband(int fd, int band, const char *data, ssize_t sz, int packet_max)
+void send_sideband(int fd, int band, const char *data, ssize_t sz, int packet_max)
 {
-	ssize_t ssz = sz;
 	const char *p = data;
 
 	while (sz) {
 		unsigned n;
 		char hdr[5];
 
