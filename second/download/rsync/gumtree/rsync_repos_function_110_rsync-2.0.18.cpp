void log_open(void)
{
	static int initialised;
	int options = LOG_PID;

	if (initialised) return;
	initialised = 1;

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif

#ifdef LOG_DAEMON
	openlog("rsyncd", options, lp_syslog_facility());
#else
	openlog("rsyncd", options);
#endif

#ifndef LOG_NDELAY
	syslog(LOG_INFO,"rsyncd started\n");
#endif
}