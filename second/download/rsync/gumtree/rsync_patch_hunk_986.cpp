 		if (send_msg(msg, buf, len, !is_utf8))
 			return;
 		if (am_daemon) {
 			/* TODO: can we send the error to the user somehow? */
 			return;
 		}
+		f = stderr;
 	}
 
+output_msg:
 	switch (code) {
 	case FERROR_XFER:
 		got_xfer_error = 1;
 		/* FALL THROUGH */
 	case FERROR:
+	case FERROR_UTF8:
+	case FERROR_SOCKET:
 	case FWARNING:
 		f = stderr;
 		break;
+	case FLOG:
 	case FINFO:
-		f = am_server ? stderr : stdout;
+	case FCLIENT:
 		break;
 	default:
+		fprintf(stderr, "Unknown logcode in rwrite(): %d [%s]\n", (int)code, who_am_i());
 		exit_cleanup(RERR_MESSAGEIO);
 	}
 
-	if (progress_is_active && !am_server) {
+	if (output_needs_newline) {
 		fputc('\n', f);
-		progress_is_active = 0;
+		output_needs_newline = 0;
 	}
 
 	trailing_CR_or_NL = len && (buf[len-1] == '\n' || buf[len-1] == '\r')
 			  ? buf[--len] : 0;
 
+	if (len && buf[0] == '\r') {
+		fputc('\r', f);
+		buf++;
+		len--;
+	}
+
 #ifdef ICONV_CONST
 	if (ic != (iconv_t)-1) {
 		xbuf outbuf, inbuf;
 		char convbuf[1024];
 		int ierrno;
 
 		INIT_CONST_XBUF(outbuf, convbuf);
-		INIT_XBUF(inbuf, (char*)buf, len, -1);
+		INIT_XBUF(inbuf, (char*)buf, len, (size_t)-1);
 
 		while (inbuf.len) {
-			iconvbufs(ic, &inbuf, &outbuf, 0);
+			iconvbufs(ic, &inbuf, &outbuf, inbuf.pos ? 0 : ICB_INIT);
 			ierrno = errno;
 			if (outbuf.len) {
 				filtered_fwrite(f, convbuf, outbuf.len, 0);
 				outbuf.len = 0;
 			}
 			if (!ierrno || ierrno == E2BIG)
