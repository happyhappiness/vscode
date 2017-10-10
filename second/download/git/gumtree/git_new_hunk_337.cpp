static int checkout_merged(int pos, const struct checkout *state)
{
	struct cache_entry *ce = active_cache[pos];
	const char *path = ce->name;
	mmfile_t ancestor, ours, theirs;
	int status;
	struct object_id oid;
	mmbuffer_t result_buf;
	struct object_id threeway[3];
	unsigned mode = 0;

	memset(threeway, 0, sizeof(threeway));
	while (pos < active_nr) {
		int stage;
		stage = ce_stage(ce);
		if (!stage || strcmp(path, ce->name))
			break;
		oidcpy(&threeway[stage - 1], &ce->oid);
		if (stage == 2)
			mode = create_ce_mode(ce->ce_mode);
		pos++;
		ce = active_cache[pos];
	}
	if (is_null_oid(&threeway[1]) || is_null_oid(&threeway[2]))
		return error(_("path '%s' does not have necessary versions"), path);

	read_mmblob(&ancestor, &threeway[0]);
	read_mmblob(&ours, &threeway[1]);
	read_mmblob(&theirs, &threeway[2]);

	/*
	 * NEEDSWORK: re-create conflicts from merges with
	 * merge.renormalize set, too
	 */
	status = ll_merge(&result_buf, path, &ancestor, "base",
