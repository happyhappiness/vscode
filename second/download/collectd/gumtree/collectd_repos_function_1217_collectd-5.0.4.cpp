static int collectd_stop (void)
{
	if (0 == collectd_pid)
		return 0;

	if (0 != kill (collectd_pid, SIGTERM)) {
		syslog (LOG_ERR, "Error: kill() failed: %s", strerror (errno));
		return -1;
	}
	return 0;
}