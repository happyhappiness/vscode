			return -1;
		}
	} else if (copy_fd(orig_fd, fd)) {
		int save_errno = errno;

		if (flags & LOCK_DIE_ON_ERROR)
			exit(128);
		close(orig_fd);
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	} else {
		close(orig_fd);
