	lock = lock_ref_sha1_basic(oldrefname, NULL, NULL, 0, NULL);
	if (!lock) {
		error("unable to lock %s for rollback", oldrefname);
		goto rollbacklog;
	}

	flag = log_all_ref_updates;
	log_all_ref_updates = 0;
	if (write_ref_sha1(lock, orig_sha1, NULL))
		error("unable to write current sha1 into %s", oldrefname);
	log_all_ref_updates = flag;

