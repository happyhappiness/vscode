static void init_globals(void)
{
#ifdef LOG_DAEMON
	Globals.syslog_facility = LOG_DAEMON;
#endif
	Globals.lock_file = "/var/run/rsyncd.lock";
}