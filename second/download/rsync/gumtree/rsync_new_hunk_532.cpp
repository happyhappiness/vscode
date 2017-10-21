  */
#include "rsync.h"

static FILE *logfile;


static void logit(int priority, char *buf)
{
	if (logfile) {
		fprintf(logfile,"%s [%d] %s", 
			timestring(time(NULL)), (int)getpid(), buf);
		fflush(logfile);
	} else {
		syslog(priority, "%s", buf);
	}
}

void log_open(void)
{
	static int initialised;
	int options = LOG_PID;
	time_t t;
	char *logf;

	if (initialised) return;
	initialised = 1;

	/* this looks pointless, but it is needed in order for the
	   C library on some systems to fetch the timezone info
	   before the chroot */
	t = time(NULL);
	localtime(&t);

	/* optionally use a log file instead of syslog */
	logf = lp_log_file();
	if (logf && *logf) {
		extern int orig_umask;
		int old_umask = umask(022 | orig_umask);
		logfile = fopen(logf, "a");
		umask(old_umask);
		return;
	}

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif
