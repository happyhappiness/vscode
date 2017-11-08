static int merge_entry(int pos, const char *path)
{
	int found;
	const char *arguments[] = { pgm, "", "", "", path, "", "", "", NULL };
	char hexbuf[4][GIT_MAX_HEXSZ + 1];
	char ownbuf[4][60];

	if (pos >= active_nr)
		die("git merge-index: %s not in the cache", path);
	found = 0;
	do {
		const struct cache_entry *ce = active_cache[pos];
		int stage = ce_stage(ce);

		if (strcmp(ce->name, path))
			break;
		found++;
		oid_to_hex_r(hexbuf[stage], &ce->oid);
		xsnprintf(ownbuf[stage], sizeof(ownbuf[stage]), "%o", ce->ce_mode);
		arguments[stage] = hexbuf[stage];
		arguments[stage + 4] = ownbuf[stage];
	} while (++pos < active_nr);
	if (!found)
		die("git merge-index: %s not in the cache", path);

	if (run_command_v_opt(arguments, 0)) {
		if (one_shot)
			err++;
		else {
			if (!quiet)
				die("merge program failed");
			exit(1);
		}
	}
	return found;
}