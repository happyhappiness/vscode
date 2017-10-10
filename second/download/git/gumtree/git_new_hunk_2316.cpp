		error("Trying to write non-commit object %s to branch %s",
			sha1_to_hex(sha1), lock->ref_name);
		unlock_ref(lock);
		errno = EINVAL;
		return -1;
	}
	if (write_in_full(lock->lk->fd, sha1_to_hex(sha1), 40) != 40 ||
	    write_in_full(lock->lk->fd, &term, 1) != 1 ||
	    close_ref(lock) < 0) {
		int save_errno = errno;
		error("Couldn't write %s", lock->lk->filename.buf);
		unlock_ref(lock);
		errno = save_errno;
		return -1;
