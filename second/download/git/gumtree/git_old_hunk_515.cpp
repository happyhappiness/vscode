
	/*
	 * The reflog file is locked by holding the lock on the
	 * reference itself, plus we might need to update the
	 * reference if --updateref was specified:
	 */
	lock = lock_ref_sha1_basic(refname, sha1, NULL, NULL, REF_NODEREF,
				   &type, &err);
	if (!lock) {
		error("cannot lock ref '%s': %s", refname, err.buf);
		strbuf_release(&err);
		return -1;
	}
