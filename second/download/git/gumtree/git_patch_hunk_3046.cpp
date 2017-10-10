 	struct strbuf sb = STRBUF_INIT;
 	if (strbuf_getcwd(&sb))
 		die_errno(_("unable to get current working directory"));
 	return strbuf_detach(&sb, NULL);
 }
 
+int xsnprintf(char *dst, size_t max, const char *fmt, ...)
+{
+	va_list ap;
+	int len;
+
+	va_start(ap, fmt);
+	len = vsnprintf(dst, max, fmt, ap);
+	va_end(ap);
+
+	if (len < 0)
+		die("BUG: your snprintf is broken");
+	if (len >= max)
+		die("BUG: attempt to snprintf into too-small buffer");
+	return len;
+}
+
 static int write_file_v(const char *path, int fatal,
 			const char *fmt, va_list params)
 {
 	struct strbuf sb = STRBUF_INIT;
 	int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
 	if (fd < 0) {
