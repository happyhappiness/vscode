void log_open()
{
	if (logfname && !logfile) {
		extern int orig_umask;
		int old_umask = umask(022 | orig_umask);
		logfile = fopen(logfname, "a");
		umask(old_umask);
	}
}