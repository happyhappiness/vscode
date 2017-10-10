
	if (log && rename_tmp_log(newrefname))
		goto rollback;

	logmoved = log;

	lock = lock_ref_sha1_basic(newrefname, NULL, NULL, 0, NULL);
	if (!lock) {
		error("unable to lock %s for update", newrefname);
		goto rollback;
	}
	lock->force_write = 1;
	hashcpy(lock->old_sha1, orig_sha1);
