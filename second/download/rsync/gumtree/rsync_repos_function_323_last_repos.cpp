static void syslog_init()
{
	static int been_here = 0;
	int options = LOG_PID;

	if (been_here)
		return;
	been_here = 1;

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif

#ifdef LOG_DAEMON
	openlog("rsyncd", options, lp_syslog_facility(module_id));
#else
	openlog("rsyncd", options);
#endif

#ifndef LOG_NDELAY
	logit(LOG_INFO, "rsyncd started\n");
#endif
}