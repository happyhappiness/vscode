	    commit_ref_update(refs, lock, orig_sha1, logmsg, &err)) {
		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}

	return 0;

 rollback:
	lock = lock_ref_sha1_basic(refs, oldrefname, NULL, NULL, NULL,
				   REF_NODEREF, NULL, &err);
	if (!lock) {
		error("unable to lock %s for rollback: %s", oldrefname, err.buf);
