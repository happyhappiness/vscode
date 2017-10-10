	ret = handle_cache(path, sha1, NULL);
	if (ret < 1)
		return error("Could not parse conflict hunks in '%s'", path);

	/* Nuke the recorded resolution for the conflict */
	id = new_rerere_id(sha1);
	filename = rerere_path(id, "postimage");
	if (unlink(filename))
		return (errno == ENOENT
			? error("no remembered resolution for %s", path)
			: error("cannot unlink %s: %s", filename, strerror(errno)));

	/*
	 * Update the preimage so that the user can resolve the
	 * conflict in the working tree, run us again to record
	 * the postimage.
	 */
