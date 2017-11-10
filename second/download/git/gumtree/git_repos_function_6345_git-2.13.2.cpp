static int files_log_ref_write(struct files_ref_store *refs,
			       const char *refname, const unsigned char *old_sha1,
			       const unsigned char *new_sha1, const char *msg,
			       int flags, struct strbuf *err)
{
	int logfd, result;

	if (log_all_ref_updates == LOG_REFS_UNSET)
		log_all_ref_updates = is_bare_repository() ? LOG_REFS_NONE : LOG_REFS_NORMAL;

	result = log_ref_setup(refs, refname,
			       flags & REF_FORCE_CREATE_REFLOG,
			       &logfd, err);

	if (result)
		return result;

	if (logfd < 0)
		return 0;
	result = log_ref_write_fd(logfd, old_sha1, new_sha1,
				  git_committer_info(0), msg);
	if (result) {
		struct strbuf sb = STRBUF_INIT;
		int save_errno = errno;

		files_reflog_path(refs, &sb, refname);
		strbuf_addf(err, "unable to append to '%s': %s",
			    sb.buf, strerror(save_errno));
		strbuf_release(&sb);
		close(logfd);
		return -1;
	}
	if (close(logfd)) {
		struct strbuf sb = STRBUF_INIT;
		int save_errno = errno;

		files_reflog_path(refs, &sb, refname);
		strbuf_addf(err, "unable to append to '%s': %s",
			    sb.buf, strerror(save_errno));
		strbuf_release(&sb);
		return -1;
	}
	return 0;
}