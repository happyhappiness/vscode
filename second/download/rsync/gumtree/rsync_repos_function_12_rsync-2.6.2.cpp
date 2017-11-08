static void init_globals(void)
{
	memset(&Globals, 0, sizeof Globals);
#ifdef LOG_DAEMON
	Globals.syslog_facility = LOG_DAEMON;
#endif
	Globals.max_verbosity = 1;
}