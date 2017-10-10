		error("unable to create directory for %s", ref_file);
		goto error_return;
	}

	lock->lock_fd = hold_lock_file_for_update(lock->lk, ref_file, lflags);
	if (lock->lock_fd < 0) {
		if (errno == ENOENT && --attempts_remaining > 0)
			/*
			 * Maybe somebody just deleted one of the
			 * directories leading to ref_file.  Try
			 * again:
			 */
			goto retry;
		else
			unable_to_lock_die(ref_file, errno);
	}
	return old_sha1 ? verify_lock(lock, old_sha1, mustexist) : lock;

 error_return:
	unlock_ref(lock);
	errno = last_errno;
