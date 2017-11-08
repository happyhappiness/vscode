void log_init(void)
{
	time_t t;

	if (log_initialised)
		return;
	log_initialised = 1;

	/* this looks pointless, but it is needed in order for the
	 * C library on some systems to fetch the timezone info
	 * before the chroot */
	t = time(NULL);
	localtime(&t);

	/* optionally use a log file instead of syslog */
	logfname = lp_log_file();
	if (logfname && *logfname)
		logfile_open();
	else
		syslog_init();
}