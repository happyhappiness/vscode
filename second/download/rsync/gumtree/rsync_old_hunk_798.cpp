	return NULL;
}


static void logit(int priority, char *buf)
{
	if (logfname) {
		if (!logfile)
			log_open();
		fprintf(logfile,"%s [%d] %s",
			timestring(time(NULL)), (int)getpid(), buf);
		fflush(logfile);
	} else {
		syslog(priority, "%s", buf);
	}
}

void log_init(void)
{
	int options = LOG_PID;
	time_t t;

	if (log_initialised)
		return;
	log_initialised = 1;

	/* this looks pointless, but it is needed in order for the
	 * C library on some systems to fetch the timezone info
	 * before the chroot */
	t = time(NULL);
	localtime(&t);

	/* optionally use a log file instead of syslog */
	logfname = lp_log_file();
	if (logfname) {
		if (*logfname) {
			log_open();
			return;
		}
		logfname = NULL;
	}

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif

#ifdef LOG_DAEMON
	openlog("rsyncd", options, lp_syslog_facility());
#else
	openlog("rsyncd", options);
#endif

#ifndef LOG_NDELAY
	logit(LOG_INFO,"rsyncd started\n");
#endif
}

void log_open(void)
{
	if (logfname && !logfile) {
		extern int orig_umask;
		int old_umask = umask(022 | orig_umask);
		logfile = fopen(logfname, "a");
		umask(old_umask);
		if (!logfile) {
			am_daemon = 0; /* avoid trying to log again */
			rsyserr(FERROR, errno, "fopen() of log-file failed");
			exit_cleanup(RERR_LOG_FAILURE);
		}
	}
}

void log_close(void)
{
	if (logfile) {
		fclose(logfile);
		logfile = NULL;
	}
}

/* this is the underlying (unformatted) rsync debugging function. Call
 * it with FINFO, FERROR or FLOG */
void rwrite(enum logcode code, char *buf, int len)
{
	FILE *f = NULL;
	/* recursion can happen with certain fatal conditions */
