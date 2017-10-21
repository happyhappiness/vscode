 
 		if (code == FLOG || (am_daemon && !am_server))
 			return;
 	} else if (code == FLOG)
 		return;
 
-	if (quiet && code != FERROR)
+	if (quiet && code == FINFO)
 		return;
 
 	if (am_server) {
+		enum msgcode msg = (enum msgcode)code;
+		if (protocol_version < 30) {
+			if (msg == MSG_ERROR)
+				msg = MSG_ERROR_XFER;
+			else if (msg == MSG_WARNING)
+				msg = MSG_INFO;
+		}
 		/* Pass the message to the non-server side. */
-		if (send_msg((enum msgcode)code, buf, len))
+		if (send_msg(msg, buf, len, !is_utf8))
 			return;
 		if (am_daemon) {
 			/* TODO: can we send the error to the user somehow? */
 			return;
 		}
 	}
 
 	switch (code) {
+	case FERROR_XFER:
+		got_xfer_error = 1;
+		/* FALL THROUGH */
 	case FERROR:
-		log_got_error = 1;
+	case FWARNING:
 		f = stderr;
 		break;
 	case FINFO:
 		f = am_server ? stderr : stdout;
 		break;
 	default:
 		exit_cleanup(RERR_MESSAGEIO);
 	}
 
 	trailing_CR_or_NL = len && (buf[len-1] == '\n' || buf[len-1] == '\r')
 			  ? buf[--len] : 0;
 
-#if defined HAVE_ICONV_OPEN && defined HAVE_ICONV_H
-	if (ic_chck != (iconv_t)-1) {
+#ifdef ICONV_CONST
+	if (ic != (iconv_t)-1) {
+		xbuf outbuf, inbuf;
 		char convbuf[1024];
-		char *in_buf = buf, *out_buf = convbuf;
-		size_t in_cnt = len, out_cnt = sizeof convbuf - 1;
+		int ierrno;
+
+		INIT_CONST_XBUF(outbuf, convbuf);
+		INIT_XBUF(inbuf, (char*)buf, len, -1);
 
-		iconv(ic_chck, NULL, 0, NULL, 0);
-		while (iconv(ic_chck, &in_buf,&in_cnt,
-				 &out_buf,&out_cnt) == (size_t)-1) {
-			if (out_buf != convbuf) {
-				filtered_fwrite(f, convbuf, out_buf - convbuf, 0);
-				out_buf = convbuf;
-				out_cnt = sizeof convbuf - 1;
+		while (inbuf.len) {
+			iconvbufs(ic, &inbuf, &outbuf, 0);
+			ierrno = errno;
+			if (outbuf.len) {
+				filtered_fwrite(f, convbuf, outbuf.len, 0);
+				outbuf.len = 0;
 			}
-			if (errno == E2BIG)
+			if (!ierrno || ierrno == E2BIG)
 				continue;
-			fprintf(f, "\\#%03o", *(uchar*)in_buf++);
-			in_cnt--;
+			fprintf(f, "\\#%03o", CVAL(inbuf.buf, inbuf.pos++));
+			inbuf.len--;
 		}
-		if (out_buf != convbuf)
-			filtered_fwrite(f, convbuf, out_buf - convbuf, 0);
 	} else
 #endif
 		filtered_fwrite(f, buf, len, !allow_8bit_chars);
 
 	if (trailing_CR_or_NL) {
 		fputc(trailing_CR_or_NL, f);
 		fflush(f);
 	}
 }
 
-/* This is the rsync debugging function. Call it with FINFO, FERROR or
- * FLOG. */
+/* This is the rsync debugging function. Call it with FINFO, FERROR_*,
+ * FWARNING, FLOG, or FCLIENT. */
 void rprintf(enum logcode code, const char *format, ...)
 {
 	va_list ap;
 	char buf[BIGPATHBUFLEN];
 	size_t len;
 
