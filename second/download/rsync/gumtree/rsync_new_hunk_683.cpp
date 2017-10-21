
static void logit(int priority, char *buf)
{
	if (logfname) {
		if (!logfile)
			log_open();
		fprintf(logfile,"%s [%d] %s",
			timestring(time(NULL)), (int)getpid(), buf);
		fflush(logfile);
	} else {
		syslog(priority, "%s", buf);
	}
}
