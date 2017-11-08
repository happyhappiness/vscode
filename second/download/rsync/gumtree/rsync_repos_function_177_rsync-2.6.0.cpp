void log_init(void)
{
	int options = LOG_PID;
	time_t t;

	if (log_initialised) return;
	log_initialised = 1;

	/* this looks pointless, but it is needed in order for the
	 * C library on some systems to fetch the timezone info
	 * before the chroot */
	t = time(NULL);
	localtime(&t);

	/* optionally use a log file instead of syslog */
	logfname = lp_log_file();
	if (logfname) {
		if (*logfname) {
			log_open();
			return;
		}
		logfname = NULL;
	}

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif

#ifdef LOG_DAEMON
	openlog("rsyncd", options, lp_syslog_facility());
#else
	openlog("rsyncd", options);
#endif

#ifndef LOG_NDELAY
	logit(LOG_INFO,"rsyncd started\n");
#endif
}