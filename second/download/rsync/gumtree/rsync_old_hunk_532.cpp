  */
#include "rsync.h"

static FILE *logfile;


/****************************************************************************
  return the date and time as a string
****************************************************************************/
static char *timestring(void )
{
	static char TimeBuf[200];
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);

#ifdef HAVE_STRFTIME
	strftime(TimeBuf,sizeof(TimeBuf)-1,"%Y/%m/%d %T",tm);
#else
	strlcpy(TimeBuf, asctime(tm), sizeof(TimeBuf)-1);
#endif

	if (TimeBuf[strlen(TimeBuf)-1] == '\n') {
		TimeBuf[strlen(TimeBuf)-1] = 0;
	}

	return(TimeBuf);
}

static void logit(int priority, char *buf)
{
	if (logfile) {
		fprintf(logfile,"%s  %s", timestring(), buf);
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

	if (initialised) return;
	initialised = 1;

	if (lp_log_file()) {
		logfile = fopen(lp_log_file(), "a");
		return;
	}

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif
