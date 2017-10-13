int hold_lock_file_for_append(struct lock_file *lk, const char *path, int flags)
{
	int fd, orig_fd;

	fd = lock_file(lk, path, flags);
	if (fd < 0) {
		if (flags & LOCK_DIE_ON_ERROR)
			unable_to_lock_die(path, errno);
		return fd;
	}

	orig_fd = open(path, O_RDONLY);
	if (orig_fd < 0) {
		if (errno != ENOENT) {
			int save_errno = errno;

			if (flags & LOCK_DIE_ON_ERROR)
				die("cannot open '%s' for copying", path);
			rollback_lock_file(lk);
			error("cannot open '%s' for copying", path);
			errno = save_errno;
			return -1;
		}
	} else if (copy_fd(orig_fd, fd)) {
		int save_errno = errno;

		if (flags & LOCK_DIE_ON_ERROR)
			die("failed to prepare '%s' for appending", path);
		close(orig_fd);
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	} else {
		close(orig_fd);
	}
	return fd;
}