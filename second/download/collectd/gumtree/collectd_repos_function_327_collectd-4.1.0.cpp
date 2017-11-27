static void sl_log (int severity, const char *msg)
{
	if (severity > log_level)
		return;

	syslog (severity, "%s", msg);
}