	while (buf < cp && isspace(cp[-1]))
		cp--;
	*cp++ = '\n';
	return cp - buf;
}

int log_ref_setup(const char *refname, char *logfile, int bufsize)
{
	int logfd, oflags = O_APPEND | O_WRONLY;

	git_snpath(logfile, bufsize, "logs/%s", refname);
	if (log_all_ref_updates &&
	    (starts_with(refname, "refs/heads/") ||
	     starts_with(refname, "refs/remotes/") ||
	     starts_with(refname, "refs/notes/") ||
	     !strcmp(refname, "HEAD"))) {
		if (safe_create_leading_directories(logfile) < 0)
			return error("unable to create directory for %s",
				     logfile);
		oflags |= O_CREAT;
	}

	logfd = open(logfile, oflags, 0666);
	if (logfd < 0) {
		if (!(oflags & O_CREAT) && errno == ENOENT)
			return 0;

		if ((oflags & O_CREAT) && errno == EISDIR) {
			if (remove_empty_directories(logfile)) {
				return error("There are still logs under '%s'",
					     logfile);
			}
			logfd = open(logfile, oflags, 0666);
		}

		if (logfd < 0)
			return error("Unable to append to %s: %s",
				     logfile, strerror(errno));
	}

	adjust_shared_perm(logfile);
	close(logfd);
	return 0;
}
