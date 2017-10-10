static int err;

static int merge_entry(int pos, const char *path)
{
	int found;
	const char *arguments[] = { pgm, "", "", "", path, "", "", "", NULL };
	char hexbuf[4][60];
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
		strcpy(hexbuf[stage], sha1_to_hex(ce->sha1));
		sprintf(ownbuf[stage], "%o", ce->ce_mode);
		arguments[stage] = hexbuf[stage];
		arguments[stage + 4] = ownbuf[stage];
	} while (++pos < active_nr);
	if (!found)
		die("git merge-index: %s not in the cache", path);

