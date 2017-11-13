static int lock_file(struct lock_file *lk, const char *path, int flags)
{
	/*
	 * subtract 5 from size to make sure there's room for adding
	 * ".lock" for the lock file name
	 */
	static const size_t max_path_len = sizeof(lk->filename) - 5;

	if (strlen(path) >= max_path_len) {
		errno = ENAMETOOLONG;
		return -1;
	}
	strcpy(lk->filename, path);
	if (!(flags & LOCK_NODEREF))
		resolve_symlink(lk->filename, max_path_len);
	strcat(lk->filename, ".lock");
	lk->fd = open(lk->filename, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (0 <= lk->fd) {
		if (!lock_file_list) {
			sigchain_push_common(remove_lock_file_on_signal);
			atexit(remove_lock_file);
		}
		lk->owner = getpid();
		if (!lk->on_list) {
			lk->next = lock_file_list;
			lock_file_list = lk;
			lk->on_list = 1;
		}
		if (adjust_shared_perm(lk->filename)) {
			int save_errno = errno;
			error("cannot fix permission bits on %s",
			      lk->filename);
			errno = save_errno;
			return -1;
		}
	}
	else
		lk->filename[0] = 0;
	return lk->fd;
}