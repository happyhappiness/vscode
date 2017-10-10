 	if (fflush(f)) {
 		check_pipe(errno);
 		die_errno("write failure on '%s'", desc);
 	}
 }
 
+void fprintf_or_die(FILE *f, const char *fmt, ...)
+{
+	va_list ap;
+	int ret;
+
+	va_start(ap, fmt);
+	ret = vfprintf(f, fmt, ap);
+	va_end(ap);
+
+	if (ret < 0) {
+		check_pipe(errno);
+		die_errno("write error");
+	}
+}
+
 void fsync_or_die(int fd, const char *msg)
 {
 	if (fsync(fd) < 0) {
 		die_errno("fsync error on '%s'", msg);
 	}
 }
