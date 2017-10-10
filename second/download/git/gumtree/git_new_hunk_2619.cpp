	int fd = lock_file_timeout(lk, path, flags, timeout_ms);
	if (fd < 0 && (flags & LOCK_DIE_ON_ERROR))
		unable_to_lock_die(path, errno);
	return fd;
}

char *get_locked_file_path(struct lock_file *lk)
{
	struct strbuf ret = STRBUF_INIT;

	strbuf_addstr(&ret, get_tempfile_path(&lk->tempfile));
	if (ret.len <= LOCK_SUFFIX_LEN ||
	    strcmp(ret.buf + ret.len - LOCK_SUFFIX_LEN, LOCK_SUFFIX))
		die("BUG: get_locked_file_path() called for malformed lock object");
	/* remove ".lock": */
	strbuf_setlen(&ret, ret.len - LOCK_SUFFIX_LEN);
	return strbuf_detach(&ret, NULL);
}

int commit_lock_file(struct lock_file *lk)
{
	char *result_path = get_locked_file_path(lk);

	if (commit_lock_file_to(lk, result_path)) {
		int save_errno = errno;
		free(result_path);
		errno = save_errno;
		return -1;
	}
	free(result_path);
	return 0;
}
