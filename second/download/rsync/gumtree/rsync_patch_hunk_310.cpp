 		mkdir(fname,0777 & ~orig_umask); 
 		*p = '/';
 		p++;
 	}
 	return 0;
 }
+
+
+/* Write LEN bytes at PTR to descriptor DESC, retrying if interrupted.
+   Return LEN upon success, write's (negative) error code otherwise.  
+
+   derived from GNU C's cccp.c.
+*/
+int full_write(int desc, char *ptr, int len)
+{
+	int total_written;
+	
+	total_written = 0;
+	while (len > 0) {
+		int written = write (desc, ptr, len);
+		if (written < 0)  {
+#ifdef EINTR
+			if (errno == EINTR)
+				continue;
+#endif
+			return written;
+		}
+		total_written += written;
+		ptr += written;
+		len -= written;
+	}
+	return total_written;
+}
+
+/* Read LEN bytes at PTR from descriptor DESC, retrying if interrupted.
+   Return the actual number of bytes read, zero for EOF, or negative
+   for an error.  
+
+   derived from GNU C's cccp.c. */
+int safe_read(int desc, char *ptr, int len)
+{
+	int n_chars;
+ 
+	if (len <= 0)
+		return len;
+ 
+#ifdef EINTR
+	do {
+		n_chars = read(desc, ptr, len);
+	} while (n_chars < 0 && errno == EINTR);
+#else
+	n_chars = read(desc, ptr, len);
+#endif
+ 
+	return n_chars;
+}
+
+
+/* copy a file - this is used in conjunction with the --temp-dir option */
+int copy_file(char *source, char *dest, mode_t mode)
+{
+	int ifd;
+	int ofd;
+	char buf[1024 * 8];
+	int len;   /* Number of bytes read into `buf'. */
+
+	ifd = open(source, O_RDONLY);
+	if (ifd == -1) {
+		fprintf(FERROR,"open %s: %s\n",
+			source,strerror(errno));
+		return -1;
+	}
+
+	if (unlink(dest) && errno != ENOENT) {
+		fprintf(FERROR,"unlink %s: %s\n",
+			dest,strerror(errno));
+		return -1;
+	}
+
+	ofd = open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode);
+	if (ofd < 0) {
+		fprintf(FERROR,"open %s: %s\n",
+			dest,strerror(errno));
+		close(ifd);
+		return -1;
+	}
+
+	while ((len = safe_read(ifd, buf, sizeof(buf))) > 0) {
+		if (full_write(ofd, buf, len) < 0) {
+			fprintf(FERROR,"write %s: %s\n",
+				dest,strerror(errno));
+			close(ifd);
+			close(ofd);
+			return -1;
+		}
+	}
+
+	close(ifd);
+	close(ofd);
+
+	if (len < 0) {
+		fprintf(FERROR,"read %s: %s\n",
+			source,strerror(errno));
+		return -1;
+	}
+
+	return 0;
+}
