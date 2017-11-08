static void logit(int priority, char *buf)
{
	if (logfile_was_closed)
		logfile_reopen();
	if (logfile) {
		fprintf(logfile,"%s [%d] %s",
			timestring(time(NULL)), (int)getpid(), buf);
		fflush(logfile);
	} else {
		syslog(priority, "%s", buf);
	}
}