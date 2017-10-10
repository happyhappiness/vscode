				   REF_NODEREF, NULL, &err);
	if (!lock) {
		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}
	hashcpy(lock->old_oid.hash, orig_sha1);

	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
	    commit_ref_update(refs, lock, orig_sha1, logmsg, &err)) {
		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}

	ret = 0;
