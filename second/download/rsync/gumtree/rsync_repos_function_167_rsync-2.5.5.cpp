void log_close()
{
	if (logfile) {
		fclose(logfile);
		logfile = NULL;
	}
}