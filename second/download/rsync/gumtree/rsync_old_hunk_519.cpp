  logging and utility functions

  tridge, May 1998
  */
#include "rsync.h"


void log_open(void)
{
	static int initialised;
	int options = LOG_PID;
	time_t t;

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

	/* this looks pointless, but it is needed in order for the
	   C library on some systems to fetch the timezone info
	   before the chroot */
	t = time(NULL);
