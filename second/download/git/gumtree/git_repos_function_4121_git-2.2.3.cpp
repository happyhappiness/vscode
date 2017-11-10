static int checkout_merged(int pos, struct checkout *state)
{
	struct cache_entry *ce = active_cache[pos];
	const char *path = ce->name;
	mmfile_t ancestor, ours, theirs;
	int status;
	unsigned char sha1[20];
	mmbuffer_t result_buf;
	unsigned char threeway[3][20];
	unsigned mode = 0;

	memset(threeway, 0, sizeof(threeway));
	while (pos < active_nr) {
		int stage;
		stage = ce_stage(ce);
		if (!stage || strcmp(path, ce->name))
			break;
		hashcpy(threeway[stage - 1], ce->sha1);
		if (stage == 2)
			mode = create_ce_mode(ce->ce_mode);
		pos++;
		ce = active_cache[pos];
	}
	if (is_null_sha1(threeway[1]) || is_null_sha1(threeway[2]))
		return error(_("path '%s' does not have necessary versions"), path);

	read_mmblob(&ancestor, threeway[0]);
	read_mmblob(&ours, threeway[1]);
	read_mmblob(&theirs, threeway[2]);

	/*
	 * NEEDSWORK: re-create conflicts from merges with
	 * merge.renormalize set, too
	 */
	status = ll_merge(&result_buf, path, &ancestor, "base",
			  &ours, "ours", &theirs, "theirs", NULL);
	free(ancestor.ptr);
	free(ours.ptr);
	free(theirs.ptr);
	if (status < 0 || !result_buf.ptr) {
		free(result_buf.ptr);
		return error(_("path '%s': cannot merge"), path);
	}

	/*
	 * NEEDSWORK:
	 * There is absolutely no reason to write this as a blob object
	 * and create a phony cache entry just to leak.  This hack is
	 * primarily to get to the write_entry() machinery that massages
	 * the contents to work-tree format and writes out which only
	 * allows it for a cache entry.  The code in write_entry() needs
	 * to be refactored to allow us to feed a <buffer, size, mode>
	 * instead of a cache entry.  Such a refactoring would help
	 * merge_recursive as well (it also writes the merge result to the
	 * object database even when it may contain conflicts).
	 */
	if (write_sha1_file(result_buf.ptr, result_buf.size,
			    blob_type, sha1))
		die(_("Unable to add merge result for '%s'"), path);
	ce = make_cache_entry(mode, sha1, path, 2, 0);
	if (!ce)
		die(_("make_cache_entry failed for path '%s'"), path);
	status = checkout_entry(ce, state, NULL);
	return status;
}