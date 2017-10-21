
  tridge, May 1998
  */
#include "rsync.h"

static FILE *logfile;


static void logit(int priority, char *buf)
{
	if (logfile) {
		fprintf(logfile,"%s [%d] %s", 
			timestring(time(NULL)), (int)getpid(), buf);
