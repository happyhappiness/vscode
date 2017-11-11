void logfile_reopen(void)
{
	if (logfile_was_closed) {
		logfile_was_closed = 0;
		logfile_open();
	}
}