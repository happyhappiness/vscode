void logfile_close(void)
{
	if (logfile) {
		logfile_was_closed = 1;
		fclose(logfile);
		logfile = NULL;
	}
}