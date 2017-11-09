static void logfile_open(void)
{
	mode_t old_umask = umask(022 | orig_umask);
	logfile_fp = fopen(logfile_name, "a");
	umask(old_umask);
	if (!logfile_fp) {
		int fopen_errno = errno;
		/* Rsync falls back to using syslog on failure. */
		syslog_init();
		rsyserr(FERROR, fopen_errno,
			"failed to open log-file %s", logfile_name);
		rprintf(FINFO, "Ignoring \"log file\" setting.\n");
	}
}