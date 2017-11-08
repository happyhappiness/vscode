void rprintf(int fd, const char *format, ...)
{
	va_list ap;  
	char buf[1024];
	int len;
	FILE *f=NULL;
	extern int am_daemon;

	va_start(ap, format);

#if HAVE_VSNPRINTF
	len = vsnprintf(buf, sizeof(buf)-1, format, ap);
#else
	vsprintf(buf, format, ap);
	len = strlen(buf);
#endif
	va_end(ap);

	if (len < 0) exit_cleanup(1);

	if (len > sizeof(buf)-1) exit_cleanup(1);

	buf[len] = 0;

	if (am_daemon) {
		static int initialised;
		int priority = LOG_INFO;
		if (fd == FERROR) priority = LOG_WARNING;

		if (!initialised) {
			initialised = 1;
#ifdef LOG_DAEMON
			openlog("rsyncd", LOG_PID, lp_syslog_facility());
#else
			openlog("rsyncd", LOG_PID);
#endif
		}
		
		syslog(priority, "%s", buf);
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
}