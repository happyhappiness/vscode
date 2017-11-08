static int log_ref_write_1(const char *refname, const unsigned char *old_sha1,
			   const unsigned char *new_sha1, const char *msg,
			   struct strbuf *logfile, int flags,
			   struct strbuf *err)
{
	int logfd, result, oflags = O_APPEND | O_WRONLY;

	if (log_all_ref_updates == LOG_REFS_UNSET)
		log_all_ref_updates = is_bare_repository() ? LOG_REFS_NONE : LOG_REFS_NORMAL;

	result = log_ref_setup(refname, logfile, err, flags & REF_FORCE_CREATE_REFLOG);

	if (result)
		return result;

	logfd = open(logfile->buf, oflags);
	if (logfd < 0)
		return 0;
	result = log_ref_write_fd(logfd, old_sha1, new_sha1,
				  git_committer_info(0), msg);
	if (result) {
		strbuf_addf(err, "unable to append to '%s': %s", logfile->buf,
			    strerror(errno));
		close(logfd);
		return -1;
	}
	if (close(logfd)) {
		strbuf_addf(err, "unable to append to '%s': %s", logfile->buf,
			    strerror(errno));
		return -1;
	}
	return 0;
}