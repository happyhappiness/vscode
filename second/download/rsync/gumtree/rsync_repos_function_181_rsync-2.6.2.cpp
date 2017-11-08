void log_close(void)
{
	if (logfile) {
		fclose(logfile);
		logfile = NULL;
	}
}