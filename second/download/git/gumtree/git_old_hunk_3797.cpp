
	if (log && rename_tmp_log(newrefname))
		goto rollback;

	logmoved = log;

	lock = lock_ref_sha1_basic(newrefname, NULL, NULL, NULL, 0, NULL, &err);
	if (!lock) {
		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}
	hashcpy(lock->old_oid.hash, orig_sha1);

	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
	    commit_ref_update(lock, orig_sha1, logmsg, 0, &err)) {
		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}

	return 0;

 rollback:
	lock = lock_ref_sha1_basic(oldrefname, NULL, NULL, NULL, 0, NULL, &err);
	if (!lock) {
		error("unable to lock %s for rollback: %s", oldrefname, err.buf);
		strbuf_release(&err);
		goto rollbacklog;
	}

	flag = log_all_ref_updates;
	log_all_ref_updates = 0;
	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
	    commit_ref_update(lock, orig_sha1, NULL, 0, &err)) {
		error("unable to write current sha1 into %s: %s", oldrefname, err.buf);
		strbuf_release(&err);
	}
	log_all_ref_updates = flag;

 rollbacklog:
