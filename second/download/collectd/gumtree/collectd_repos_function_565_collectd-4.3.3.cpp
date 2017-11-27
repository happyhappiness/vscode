static int pidfile_delete (void)
{
	assert (NULL != pidfile);

	if (0 != unlink (pidfile)) {
		syslog (LOG_ERR, "Error: couldn't delete PID-file (%s): %s",
				pidfile, strerror (errno));
		return -1;
	}
	return 0;
}