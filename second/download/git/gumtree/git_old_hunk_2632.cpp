	while (buf < cp && isspace(cp[-1]))
		cp--;
	*cp++ = '\n';
	return cp - buf;
}

/* This function must set a meaningful errno on failure */
int log_ref_setup(const char *refname, struct strbuf *sb_logfile)
{
	int logfd, oflags = O_APPEND | O_WRONLY;
	char *logfile;

	strbuf_git_path(sb_logfile, "logs/%s", refname);
	logfile = sb_logfile->buf;
	/* make sure the rest of the function can't change "logfile" */
	sb_logfile = NULL;
	if (log_all_ref_updates &&
	    (starts_with(refname, "refs/heads/") ||
	     starts_with(refname, "refs/remotes/") ||
	     starts_with(refname, "refs/notes/") ||
	     !strcmp(refname, "HEAD"))) {
		if (safe_create_leading_directories(logfile) < 0) {
			int save_errno = errno;
			error("unable to create directory for %s", logfile);
			errno = save_errno;
			return -1;
		}
		oflags |= O_CREAT;
	}

	logfd = open(logfile, oflags, 0666);
	if (logfd < 0) {
		if (!(oflags & O_CREAT) && (errno == ENOENT || errno == EISDIR))
			return 0;

		if (errno == EISDIR) {
			if (remove_empty_directories(logfile)) {
				int save_errno = errno;
				error("There are still logs under '%s'",
				      logfile);
				errno = save_errno;
				return -1;
			}
			logfd = open(logfile, oflags, 0666);
		}

		if (logfd < 0) {
			int save_errno = errno;
			error("Unable to append to %s: %s", logfile,
			      strerror(errno));
			errno = save_errno;
			return -1;
		}
	}

	adjust_shared_perm(logfile);
	close(logfd);
	return 0;
}

static int log_ref_write_fd(int fd, const unsigned char *old_sha1,
			    const unsigned char *new_sha1,
			    const char *committer, const char *msg)
{
	int msglen, written;
	unsigned maxlen, len;
