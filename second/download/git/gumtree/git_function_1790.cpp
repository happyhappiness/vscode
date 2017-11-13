int reflog_expire(const char *refname, const unsigned char *sha1,
		 unsigned int flags,
		 reflog_expiry_prepare_fn prepare_fn,
		 reflog_expiry_should_prune_fn should_prune_fn,
		 reflog_expiry_cleanup_fn cleanup_fn,
		 void *policy_cb_data)
{
	static struct lock_file reflog_lock;
	struct expire_reflog_cb cb;
	struct ref_lock *lock;
	char *log_file;
	int status = 0;
	int type;

	memset(&cb, 0, sizeof(cb));
	cb.flags = flags;
	cb.policy_cb = policy_cb_data;
	cb.should_prune_fn = should_prune_fn;

	/*
	 * The reflog file is locked by holding the lock on the
	 * reference itself, plus we might need to update the
	 * reference if --updateref was specified:
	 */
	lock = lock_ref_sha1_basic(refname, sha1, NULL, 0, &type);
	if (!lock)
		return error("cannot lock ref '%s'", refname);
	if (!reflog_exists(refname)) {
		unlock_ref(lock);
		return 0;
	}

	log_file = git_pathdup("logs/%s", refname);
	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
		/*
		 * Even though holding $GIT_DIR/logs/$reflog.lock has
		 * no locking implications, we use the lock_file
		 * machinery here anyway because it does a lot of the
		 * work we need, including cleaning up if the program
		 * exits unexpectedly.
		 */
		if (hold_lock_file_for_update(&reflog_lock, log_file, 0) < 0) {
			struct strbuf err = STRBUF_INIT;
			unable_to_lock_message(log_file, errno, &err);
			error("%s", err.buf);
			strbuf_release(&err);
			goto failure;
		}
		cb.newlog = fdopen_lock_file(&reflog_lock, "w");
		if (!cb.newlog) {
			error("cannot fdopen %s (%s)",
			      reflog_lock.filename.buf, strerror(errno));
			goto failure;
		}
	}

	(*prepare_fn)(refname, sha1, cb.policy_cb);
	for_each_reflog_ent(refname, expire_reflog_ent, &cb);
	(*cleanup_fn)(cb.policy_cb);

	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
		/*
		 * It doesn't make sense to adjust a reference pointed
		 * to by a symbolic ref based on expiring entries in
		 * the symbolic reference's reflog. Nor can we update
		 * a reference if there are no remaining reflog
		 * entries.
		 */
		int update = (flags & EXPIRE_REFLOGS_UPDATE_REF) &&
			!(type & REF_ISSYMREF) &&
			!is_null_sha1(cb.last_kept_sha1);

		if (close_lock_file(&reflog_lock)) {
			status |= error("couldn't write %s: %s", log_file,
					strerror(errno));
		} else if (update &&
			(write_in_full(lock->lock_fd,
				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
			 write_str_in_full(lock->lock_fd, "\n") != 1 ||
			 close_ref(lock) < 0)) {
			status |= error("couldn't write %s",
					lock->lk->filename.buf);
			rollback_lock_file(&reflog_lock);
		} else if (commit_lock_file(&reflog_lock)) {
			status |= error("unable to commit reflog '%s' (%s)",
					log_file, strerror(errno));
		} else if (update && commit_ref(lock)) {
			status |= error("couldn't set %s", lock->ref_name);
		}
	}
	free(log_file);
	unlock_ref(lock);
	return status;

 failure:
	rollback_lock_file(&reflog_lock);
	free(log_file);
	unlock_ref(lock);
	return -1;
}