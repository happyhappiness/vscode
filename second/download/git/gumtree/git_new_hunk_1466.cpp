			     pattern);

	/*
	 * Remote HEAD must be a symref (not exactly foolproof; a remote
	 * symlink to a symref will look like a symref)
	 */
	fetch_symref("HEAD", &symref, &head_oid);
	if (!symref)
		return error("Remote HEAD is not a symref");

	/* Remote branch must not be the remote HEAD */
	for (i = 0; symref && i < MAXDEPTH; i++) {
		if (!strcmp(remote_ref->name, symref))
			return error("Remote branch %s is the current HEAD",
				     remote_ref->name);
		fetch_symref(symref, &symref, &head_oid);
	}

	/* Run extra sanity checks if delete is not forced */
	if (!force) {
		/* Remote HEAD must resolve to a known object */
		if (symref)
			return error("Remote HEAD symrefs too deep");
		if (is_null_oid(&head_oid))
			return error("Unable to resolve remote HEAD");
		if (!has_object_file(&head_oid))
			return error("Remote HEAD resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", oid_to_hex(&head_oid));

		/* Remote branch must resolve to a known object */
		if (is_null_oid(&remote_ref->old_oid))
			return error("Unable to resolve remote branch %s",
				     remote_ref->name);
		if (!has_object_file(&remote_ref->old_oid))
			return error("Remote branch %s resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", remote_ref->name, oid_to_hex(&remote_ref->old_oid));

		/* Remote branch must be an ancestor of remote HEAD */
		if (!verify_merge_base(&head_oid, remote_ref)) {
			return error("The branch '%s' is not an ancestor "
				     "of your current HEAD.\n"
				     "If you are sure you want to delete it,"
				     " run:\n\t'git http-push -D %s %s'",
				     remote_ref->name, repo->url, pattern);
		}
