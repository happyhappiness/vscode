	while (buf < cp && isspace(cp[-1]))
		cp--;
	*cp++ = '\n';
	return cp - buf;
}

static int should_autocreate_reflog(const char *refname)
{
	if (!log_all_ref_updates)
		return 0;
	return starts_with(refname, "refs/heads/") ||
		starts_with(refname, "refs/remotes/") ||
		starts_with(refname, "refs/notes/") ||
		!strcmp(refname, "HEAD");
}

/*
 * Create a reflog for a ref.  If force_create = 0, the reflog will
 * only be created for certain refs (those for which
 * should_autocreate_reflog returns non-zero.  Otherwise, create it
 * regardless of the ref name.  Fill in *err and return -1 on failure.
 */
static int log_ref_setup(const char *refname, struct strbuf *logfile, struct strbuf *err, int force_create)
{
	int logfd, oflags = O_APPEND | O_WRONLY;

	strbuf_git_path(logfile, "logs/%s", refname);
	if (force_create || should_autocreate_reflog(refname)) {
		if (safe_create_leading_directories(logfile->buf) < 0) {
			strbuf_addf(err, "unable to create directory for %s: "
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
				strbuf_addf(err, "There are still logs under "
					    "'%s'", logfile->buf);
				return -1;
			}
			logfd = open(logfile->buf, oflags, 0666);
		}

		if (logfd < 0) {
			strbuf_addf(err, "unable to append to %s: %s",
				    logfile->buf, strerror(errno));
			return -1;
		}
	}

	adjust_shared_perm(logfile->buf);
	close(logfd);
	return 0;
}


int safe_create_reflog(const char *refname, int force_create, struct strbuf *err)
{
	int ret;
	struct strbuf sb = STRBUF_INIT;

	ret = log_ref_setup(refname, &sb, err, force_create);
	strbuf_release(&sb);
	return ret;
}

static int log_ref_write_fd(int fd, const unsigned char *old_sha1,
			    const unsigned char *new_sha1,
			    const char *committer, const char *msg)
{
	int msglen, written;
	unsigned maxlen, len;
