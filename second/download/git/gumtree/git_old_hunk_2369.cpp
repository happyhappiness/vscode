		int save_errno = errno;
		error("Couldn't write %s", lock->lk->filename.buf);
		unlock_ref(lock);
		errno = save_errno;
		return -1;
	}
	clear_loose_ref_cache(&ref_cache);
	if (log_ref_write(lock->ref_name, lock->old_sha1, sha1, logmsg) < 0 ||
	    (strcmp(lock->ref_name, lock->orig_ref_name) &&
	     log_ref_write(lock->orig_ref_name, lock->old_sha1, sha1, logmsg) < 0)) {
		unlock_ref(lock);
		return -1;
