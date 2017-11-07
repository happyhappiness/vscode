static int commit_ref(struct ref_lock *lock)
{
	char *path = get_locked_file_path(lock->lk);
	struct stat st;

	if (!lstat(path, &st) && S_ISDIR(st.st_mode)) {
		/*
		 * There is a directory at the path we want to rename
		 * the lockfile to. Hopefully it is empty; try to
		 * delete it.
		 */
		size_t len = strlen(path);
		struct strbuf sb_path = STRBUF_INIT;

		strbuf_attach(&sb_path, path, len, len);

		/*
		 * If this fails, commit_lock_file() will also fail
		 * and will report the problem.
		 */
		remove_empty_directories(&sb_path);
		strbuf_release(&sb_path);
	} else {
		free(path);
	}

	if (commit_lock_file(lock->lk))
		return -1;
	return 0;
}