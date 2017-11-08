static int log_ref_write_1(const char *refname, const unsigned char *old_sha1,
			   const unsigned char *new_sha1, const char *msg,
			   struct strbuf *sb_log_file)
{
	int logfd, result, oflags = O_APPEND | O_WRONLY;
	char *log_file;

	if (log_all_ref_updates < 0)
		log_all_ref_updates = !is_bare_repository();

	result = log_ref_setup(refname, sb_log_file);
	if (result)
		return result;
	log_file = sb_log_file->buf;
	/* make sure the rest of the function can't change "log_file" */
	sb_log_file = NULL;

	logfd = open(log_file, oflags);
	if (logfd < 0)
		return 0;
	result = log_ref_write_fd(logfd, old_sha1, new_sha1,
				  git_committer_info(0), msg);
	if (result) {
		int save_errno = errno;
		close(logfd);
		error("Unable to append to %s", log_file);
		errno = save_errno;
		return -1;
	}
	if (close(logfd)) {
		int save_errno = errno;
		error("Unable to append to %s", log_file);
		errno = save_errno;
		return -1;
	}
	return 0;
}