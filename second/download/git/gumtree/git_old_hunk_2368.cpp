
	if (log && rename_tmp_log(newrefname))
		goto rollback;

	logmoved = log;

	lock = lock_ref_sha1_basic(newrefname, NULL, NULL, 0, NULL);
	if (!lock) {
		error("unable to lock %s for update", newrefname);
		goto rollback;
	}
	hashcpy(lock->old_sha1, orig_sha1);
	if (write_ref_sha1(lock, orig_sha1, logmsg)) {
		error("unable to write current sha1 into %s", newrefname);
		goto rollback;
	}

	return 0;

 rollback:
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

 rollbacklog:
	if (logmoved && rename(git_path("logs/%s", newrefname), git_path("logs/%s", oldrefname)))
		error("unable to restore logfile %s from %s: %s",
