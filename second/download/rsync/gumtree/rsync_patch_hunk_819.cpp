 	if (logfile_was_closed) {
 		logfile_was_closed = 0;
 		logfile_open();
 	}
 }
 
+static void filtered_fwrite(FILE *f, const char *buf, int len, int use_isprint)
+{
+	const char *s, *end = buf + len;
+	for (s = buf; s < end; s++) {
+		if ((s < end - 4
+		  && *s == '\\' && s[1] == '#'
+		  && isdigit(*(uchar*)(s+2))
+		  && isdigit(*(uchar*)(s+3))
+		  && isdigit(*(uchar*)(s+4)))
+		 || (*s != '\t'
+		  && ((use_isprint && !isprint(*(uchar*)s))
+		   || *(uchar*)s < ' '))) {
+			if (s != buf && fwrite(buf, s - buf, 1, f) != 1)
+				exit_cleanup(RERR_MESSAGEIO);
+			fprintf(f, "\\#%03o", *(uchar*)s);
+			buf = s + 1;
+		}
+	}
+	if (buf != end && fwrite(buf, end - buf, 1, f) != 1)
+		exit_cleanup(RERR_MESSAGEIO);
+}
+
 /* this is the underlying (unformatted) rsync debugging function. Call
- * it with FINFO, FERROR or FLOG */
+ * it with FINFO, FERROR or FLOG.  Note: recursion can happen with
+ * certain fatal conditions. */
 void rwrite(enum logcode code, char *buf, int len)
 {
+	int trailing_CR_or_NL;
 	FILE *f = NULL;
-	/* recursion can happen with certain fatal conditions */
-
-	if (quiet && code == FINFO)
-		return;
 
 	if (len < 0)
 		exit_cleanup(RERR_MESSAGEIO);
 
-	buf[len] = 0;
+	if (quiet && code == FINFO)
+		return;
 
 	if (am_server && msg_fd_out >= 0) {
 		/* Pass the message to our sibling. */
 		send_msg((enum msgcode)code, buf, len);
 		return;
 	}
 
+	if (code == FSOCKERR) /* This gets simplified for a non-sibling. */
+		code = FERROR;
+
 	if (code == FCLIENT)
 		code = FINFO;
 	else if (am_daemon) {
 		static int in_block;
 		char msg[2048];
 		int priority = code == FERROR ? LOG_WARNING : LOG_INFO;
