void logfile_close(void)
{
	if (logfile_fp) {
		logfile_was_closed = 1;
		fclose(logfile_fp);
		logfile_fp = NULL;
	}
}