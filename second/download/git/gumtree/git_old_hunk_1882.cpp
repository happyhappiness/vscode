		return -1;
	}
	if (write_in_full(lock->lock_fd, sha1_to_hex(sha1), 40) != 40 ||
	    write_in_full(lock->lock_fd, &term, 1) != 1 ||
	    close_ref(lock) < 0) {
		int save_errno = errno;
		error("Couldn't write %s", lock->lk->filename);
		unlock_ref(lock);
		errno = save_errno;
		return -1;
	}
	clear_loose_ref_cache(&ref_cache);
	if (log_ref_write(lock->ref_name, lock->old_sha1, sha1, logmsg) < 0 ||
