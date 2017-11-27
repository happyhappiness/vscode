static void logfile_log (int severity, const char *msg)
{
	if (severity > log_level)
		return;

	logfile_print (msg, time (NULL));
}