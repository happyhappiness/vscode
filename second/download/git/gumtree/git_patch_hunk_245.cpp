  */
 
 #include "cache.h"
 #include "quote.h"
 
 /* Get a trace file descriptor from "key" env variable. */
-static int get_trace_fd(const char *key, int *need_close)
+static int get_trace_fd(struct trace_key *key)
 {
-	char *trace = getenv(key);
+	static struct trace_key trace_default = { "GIT_TRACE" };
+	const char *trace;
+
+	/* use default "GIT_TRACE" if NULL */
+	if (!key)
+		key = &trace_default;
+
+	/* don't open twice */
+	if (key->initialized)
+		return key->fd;
+
+	trace = getenv(key->key);
 
 	if (!trace || !strcmp(trace, "") ||
 	    !strcmp(trace, "0") || !strcasecmp(trace, "false"))
-		return 0;
-	if (!strcmp(trace, "1") || !strcasecmp(trace, "true"))
-		return STDERR_FILENO;
-	if (strlen(trace) == 1 && isdigit(*trace))
-		return atoi(trace);
-	if (is_absolute_path(trace)) {
+		key->fd = 0;
+	else if (!strcmp(trace, "1") || !strcasecmp(trace, "true"))
+		key->fd = STDERR_FILENO;
+	else if (strlen(trace) == 1 && isdigit(*trace))
+		key->fd = atoi(trace);
+	else if (is_absolute_path(trace)) {
 		int fd = open(trace, O_WRONLY | O_APPEND | O_CREAT, 0666);
 		if (fd == -1) {
 			fprintf(stderr,
 				"Could not open '%s' for tracing: %s\n"
 				"Defaulting to tracing on stderr...\n",
 				trace, strerror(errno));
-			return STDERR_FILENO;
+			key->fd = STDERR_FILENO;
+		} else {
+			key->fd = fd;
+			key->need_close = 1;
 		}
-		*need_close = 1;
-		return fd;
+	} else {
+		fprintf(stderr, "What does '%s' for %s mean?\n"
+			"If you want to trace into a file, then please set "
+			"%s to an absolute pathname (starting with /).\n"
+			"Defaulting to tracing on stderr...\n",
+			trace, key->key, key->key);
+		key->fd = STDERR_FILENO;
 	}
 
-	fprintf(stderr, "What does '%s' for %s mean?\n", trace, key);
-	fprintf(stderr, "If you want to trace into a file, "
-		"then please set %s to an absolute pathname "
-		"(starting with /).\n", key);
-	fprintf(stderr, "Defaulting to tracing on stderr...\n");
+	key->initialized = 1;
+	return key->fd;
+}
 
-	return STDERR_FILENO;
+void trace_disable(struct trace_key *key)
+{
+	if (key->need_close)
+		close(key->fd);
+	key->fd = 0;
+	key->initialized = 1;
+	key->need_close = 0;
 }
 
 static const char err_msg[] = "Could not trace into fd given by "
 	"GIT_TRACE environment variable";
 
-static void trace_vprintf(const char *key, const char *fmt, va_list ap)
+static int prepare_trace_line(const char *file, int line,
+			      struct trace_key *key, struct strbuf *buf)
 {
-	struct strbuf buf = STRBUF_INIT;
+	static struct trace_key trace_bare = TRACE_KEY_INIT(BARE);
+	struct timeval tv;
+	struct tm tm;
+	time_t secs;
 
 	if (!trace_want(key))
-		return;
+		return 0;
 
 	set_try_to_free_routine(NULL);	/* is never reset */
-	strbuf_vaddf(&buf, fmt, ap);
-	trace_strbuf(key, &buf);
-	strbuf_release(&buf);
+
+	/* unit tests may want to disable additional trace output */
+	if (trace_want(&trace_bare))
+		return 1;
+
+	/* print current timestamp */
+	gettimeofday(&tv, NULL);
+	secs = tv.tv_sec;
+	localtime_r(&secs, &tm);
+	strbuf_addf(buf, "%02d:%02d:%02d.%06ld ", tm.tm_hour, tm.tm_min,
+		    tm.tm_sec, (long) tv.tv_usec);
+
+#ifdef HAVE_VARIADIC_MACROS
+	/* print file:line */
+	strbuf_addf(buf, "%s:%d ", file, line);
+	/* align trace output (column 40 catches most files names in git) */
+	while (buf->len < 40)
+		strbuf_addch(buf, ' ');
+#endif
+
+	return 1;
+}
+
+static void print_trace_line(struct trace_key *key, struct strbuf *buf)
+{
+	/* append newline if missing */
+	if (buf->len && buf->buf[buf->len - 1] != '\n')
+		strbuf_addch(buf, '\n');
+
+	write_or_whine_pipe(get_trace_fd(key), buf->buf, buf->len, err_msg);
+	strbuf_release(buf);
+}
+
+static void trace_vprintf_fl(const char *file, int line, struct trace_key *key,
+			     const char *format, va_list ap)
+{
+	struct strbuf buf = STRBUF_INIT;
+
+	if (!prepare_trace_line(file, line, key, &buf))
+		return;
+
+	strbuf_vaddf(&buf, format, ap);
+	print_trace_line(key, &buf);
+}
+
+static void trace_argv_vprintf_fl(const char *file, int line,
+				  const char **argv, const char *format,
+				  va_list ap)
+{
+	struct strbuf buf = STRBUF_INIT;
+
+	if (!prepare_trace_line(file, line, NULL, &buf))
+		return;
+
+	strbuf_vaddf(&buf, format, ap);
+
+	sq_quote_argv(&buf, argv, 0);
+	print_trace_line(NULL, &buf);
+}
+
+void trace_strbuf_fl(const char *file, int line, struct trace_key *key,
+		     const struct strbuf *data)
+{
+	struct strbuf buf = STRBUF_INIT;
+
+	if (!prepare_trace_line(file, line, key, &buf))
+		return;
+
+	strbuf_addbuf(&buf, data);
+	print_trace_line(key, &buf);
+}
+
+static struct trace_key trace_perf_key = TRACE_KEY_INIT(PERFORMANCE);
+
+static void trace_performance_vprintf_fl(const char *file, int line,
+					 uint64_t nanos, const char *format,
+					 va_list ap)
+{
+	struct strbuf buf = STRBUF_INIT;
+
+	if (!prepare_trace_line(file, line, &trace_perf_key, &buf))
+		return;
+
+	strbuf_addf(&buf, "performance: %.9f s", (double) nanos / 1000000000);
+
+	if (format && *format) {
+		strbuf_addstr(&buf, ": ");
+		strbuf_vaddf(&buf, format, ap);
+	}
+
+	print_trace_line(&trace_perf_key, &buf);
 }
 
-__attribute__((format (printf, 2, 3)))
-void trace_printf_key(const char *key, const char *fmt, ...)
+#ifndef HAVE_VARIADIC_MACROS
+
+void trace_printf(const char *format, ...)
 {
 	va_list ap;
-	va_start(ap, fmt);
-	trace_vprintf(key, fmt, ap);
+	va_start(ap, format);
+	trace_vprintf_fl(NULL, 0, NULL, format, ap);
 	va_end(ap);
 }
 
-void trace_printf(const char *fmt, ...)
+void trace_printf_key(struct trace_key *key, const char *format, ...)
 {
 	va_list ap;
-	va_start(ap, fmt);
-	trace_vprintf("GIT_TRACE", fmt, ap);
+	va_start(ap, format);
+	trace_vprintf_fl(NULL, 0, key, format, ap);
 	va_end(ap);
 }
 
-void trace_strbuf(const char *key, const struct strbuf *buf)
+void trace_argv_printf(const char **argv, const char *format, ...)
 {
-	int fd, need_close = 0;
-
-	fd = get_trace_fd(key, &need_close);
-	if (!fd)
-		return;
+	va_list ap;
+	va_start(ap, format);
+	trace_argv_vprintf_fl(NULL, 0, argv, format, ap);
+	va_end(ap);
+}
 
-	write_or_whine_pipe(fd, buf->buf, buf->len, err_msg);
+void trace_strbuf(const char *key, const struct strbuf *data)
+{
+	trace_strbuf_fl(NULL, 0, key, data);
+}
 
-	if (need_close)
-		close(fd);
+void trace_performance(uint64_t nanos, const char *format, ...)
+{
+	va_list ap;
+	va_start(ap, format);
+	trace_performance_vprintf_fl(NULL, 0, nanos, format, ap);
+	va_end(ap);
 }
 
-void trace_argv_printf(const char **argv, const char *fmt, ...)
+void trace_performance_since(uint64_t start, const char *format, ...)
 {
-	struct strbuf buf = STRBUF_INIT;
 	va_list ap;
-	int fd, need_close = 0;
+	va_start(ap, format);
+	trace_performance_vprintf_fl(NULL, 0, getnanotime() - start,
+				     format, ap);
+	va_end(ap);
+}
 
-	fd = get_trace_fd("GIT_TRACE", &need_close);
-	if (!fd)
-		return;
+#else
 
-	set_try_to_free_routine(NULL);	/* is never reset */
-	va_start(ap, fmt);
-	strbuf_vaddf(&buf, fmt, ap);
+void trace_printf_key_fl(const char *file, int line, struct trace_key *key,
+			 const char *format, ...)
+{
+	va_list ap;
+	va_start(ap, format);
+	trace_vprintf_fl(file, line, key, format, ap);
 	va_end(ap);
+}
 
-	sq_quote_argv(&buf, argv, 0);
-	strbuf_addch(&buf, '\n');
-	write_or_whine_pipe(fd, buf.buf, buf.len, err_msg);
-	strbuf_release(&buf);
+void trace_argv_printf_fl(const char *file, int line, const char **argv,
+			  const char *format, ...)
+{
+	va_list ap;
+	va_start(ap, format);
+	trace_argv_vprintf_fl(file, line, argv, format, ap);
+	va_end(ap);
+}
 
-	if (need_close)
-		close(fd);
+void trace_performance_fl(const char *file, int line, uint64_t nanos,
+			      const char *format, ...)
+{
+	va_list ap;
+	va_start(ap, format);
+	trace_performance_vprintf_fl(file, line, nanos, format, ap);
+	va_end(ap);
 }
 
+#endif /* HAVE_VARIADIC_MACROS */
+
+
 static const char *quote_crnl(const char *path)
 {
 	static char new_path[PATH_MAX];
 	const char *p2 = path;
 	char *p1 = new_path;
 
