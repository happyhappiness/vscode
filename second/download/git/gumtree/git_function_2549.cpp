static int commit_ref_update(struct ref_lock *lock,
			     const unsigned char *sha1, const char *logmsg,
			     int flags, struct strbuf *err)
{
	clear_loose_ref_cache(&ref_cache);
	if (log_ref_write(lock->ref_name, lock->old_oid.hash, sha1, logmsg, flags, err) < 0 ||
	    (strcmp(lock->ref_name, lock->orig_ref_name) &&
	     log_ref_write(lock->orig_ref_name, lock->old_oid.hash, sha1, logmsg, flags, err) < 0)) {
		char *old_msg = strbuf_detach(err, NULL);
		strbuf_addf(err, "Cannot update the ref '%s': %s",
			    lock->ref_name, old_msg);
		free(old_msg);
		unlock_ref(lock);
		return -1;
	}
	if (strcmp(lock->orig_ref_name, "HEAD") != 0) {
		/*
		 * Special hack: If a branch is updated directly and HEAD
		 * points to it (may happen on the remote side of a push
		 * for example) then logically the HEAD reflog should be
		 * updated too.
		 * A generic solution implies reverse symref information,
		 * but finding all symrefs pointing to the given branch
		 * would be rather costly for this rare event (the direct
		 * update of a branch) to be worth it.  So let's cheat and
		 * check with HEAD only which should cover 99% of all usage
		 * scenarios (even 100% of the default ones).
		 */
		unsigned char head_sha1[20];
		int head_flag;
		const char *head_ref;
		head_ref = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
					      head_sha1, &head_flag);
		if (head_ref && (head_flag & REF_ISSYMREF) &&
		    !strcmp(head_ref, lock->ref_name)) {
			struct strbuf log_err = STRBUF_INIT;
			if (log_ref_write("HEAD", lock->old_oid.hash, sha1,
					  logmsg, 0, &log_err)) {
				error("%s", log_err.buf);
				strbuf_release(&log_err);
			}
		}
	}
	if (commit_ref(lock)) {
		error("Couldn't set %s", lock->ref_name);
		unlock_ref(lock);
		return -1;
	}

	unlock_ref(lock);
	return 0;
}