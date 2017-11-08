void log_init(int restart)
{
	if (log_initialised) {
		if (!restart)
			return;
		if (strcmp(logfile_name, lp_log_file(module_id)) != 0) {
			if (logfile_fp) {
				fclose(logfile_fp);
				logfile_fp = NULL;
			} else
				closelog();
			logfile_name = NULL;
		} else if (*logfile_name)
			return; /* unchanged, non-empty "log file" names */
		else if (lp_syslog_facility(-1) != lp_syslog_facility(module_id))
			closelog();
		else
			return; /* unchanged syslog settings */
	} else
		log_initialised = 1;

	/* This looks pointless, but it is needed in order for the
	 * C library on some systems to fetch the timezone info
	 * before the chroot. */
	timestring(time(NULL));

	/* Optionally use a log file instead of syslog.  (Non-daemon
	 * rsyncs will have already set logfile_name, as needed.) */
	if (am_daemon && !logfile_name)
		logfile_name = lp_log_file(module_id);
	if (logfile_name && *logfile_name)
		logfile_open();
	else
		syslog_init();
}