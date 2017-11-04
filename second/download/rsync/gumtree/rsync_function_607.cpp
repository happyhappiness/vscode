static void logit(int priority, char *buf)
{
	if (logfile) {
		fprintf(logfile,"%s  %s", timestring(), buf);
		fflush(logfile);
	} else {
		syslog(priority, "%s", buf);
	}
}