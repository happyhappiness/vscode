		ret = error("unable to move logfile logs/%s to logs/"TMP_RENAMED_LOG": %s",
			    oldrefname, strerror(errno));
		goto out;
	}

	if (refs_delete_ref(&refs->base, logmsg, oldrefname,
			    orig_oid.hash, REF_NODEREF)) {
		error("unable to delete old %s", oldrefname);
		goto rollback;
	}

	/*
	 * Since we are doing a shallow lookup, oid is not the
	 * correct value to pass to delete_ref as old_oid. But that
	 * doesn't matter, because an old_oid check wouldn't add to
	 * the safety anyway; we want to delete the reference whatever
	 * its current value.
	 */
	if (!refs_read_ref_full(&refs->base, newrefname,
				RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
				oid.hash, NULL) &&
	    refs_delete_ref(&refs->base, NULL, newrefname,
			    NULL, REF_NODEREF)) {
		if (errno == EISDIR) {
			struct strbuf path = STRBUF_INIT;
			int result;

