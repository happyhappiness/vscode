static void logfile_open(void)
{
	mode_t old_umask = umask(022 | orig_umask);
	logfile = fopen(logfname, "a");
	umask(old_umask);
	if (!logfile) {
		int fopen_errno = errno;
		/* Rsync falls back to using syslog on failure. */
		syslog_init();
		rsyserr(FERROR, fopen_errno,
			"failed to open log-file %s", logfname);
		rprintf(FINFO, "Ignoring \"log file\" setting.\n");
	}
}