static int log_ref_setup(const char *refname, struct strbuf *logfile, struct strbuf *err, int force_create)
{
	int logfd, oflags = O_APPEND | O_WRONLY;

	strbuf_git_path(logfile, "logs/%s", refname);
	if (force_create || should_autocreate_reflog(refname)) {
		if (safe_create_leading_directories(logfile->buf) < 0) {
			strbuf_addf(err, "unable to create directory for '%s': "
				    "%s", logfile->buf, strerror(errno));
			return -1;
		}
		oflags |= O_CREAT;
	}

	logfd = open(logfile->buf, oflags, 0666);
	if (logfd < 0) {
		if (!(oflags & O_CREAT) && (errno == ENOENT || errno == EISDIR))
			return 0;

		if (errno == EISDIR) {
			if (remove_empty_directories(logfile)) {
				strbuf_addf(err, "there are still logs under "
					    "'%s'", logfile->buf);
				return -1;
			}
			logfd = open(logfile->buf, oflags, 0666);
		}

		if (logfd < 0) {
			strbuf_addf(err, "unable to append to '%s': %s",
				    logfile->buf, strerror(errno));
			return -1;
		}
	}

	adjust_shared_perm(logfile->buf);
	close(logfd);
	return 0;
}