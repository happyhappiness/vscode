void rprintf(int fd, const char *format, ...)
{
	va_list ap;  
	char buf[1024];
	int len;
	FILE *f=NULL;
	extern int am_daemon;
	/* recursion can happen with certain fatal conditions */
	static int depth;

	if (depth) return;

	depth++;

	va_start(ap, format);
	len = vslprintf(buf, sizeof(buf)-1, format, ap);
	va_end(ap);

	if (len < 0) exit_cleanup(1);

	if (len > sizeof(buf)-1) exit_cleanup(1);

	buf[len] = 0;

	if (am_daemon) {
		int priority = LOG_INFO;
		if (fd == FERROR) priority = LOG_WARNING;

		log_open();
		if (!io_multiplex_write(fd, buf, strlen(buf))) {
			syslog(priority, "%s", buf);
		}

		depth--;
		return;
	}

	if (fd == FERROR) {
		f = stderr;
	} 

	if (fd == FINFO) {
		extern int am_server;
		if (am_server) 
			f = stderr;
		else
			f = stdout;
	} 

	if (!f) exit_cleanup(1);

	if (fwrite(buf, len, 1, f) != 1) exit_cleanup(1);

	depth--;
}