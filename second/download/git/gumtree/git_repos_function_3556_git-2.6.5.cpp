static void diagnose_invalid_index_path(int stage,
					const char *prefix,
					const char *filename)
{
	const struct cache_entry *ce;
	int pos;
	unsigned namelen = strlen(filename);
	unsigned fullnamelen;
	char *fullname;

	if (!prefix)
		prefix = "";

	/* Wrong stage number? */
	pos = cache_name_pos(filename, namelen);
	if (pos < 0)
		pos = -pos - 1;
	if (pos < active_nr) {
		ce = active_cache[pos];
		if (ce_namelen(ce) == namelen &&
		    !memcmp(ce->name, filename, namelen))
			die("Path '%s' is in the index, but not at stage %d.\n"
			    "Did you mean ':%d:%s'?",
			    filename, stage,
			    ce_stage(ce), filename);
	}

	/* Confusion between relative and absolute filenames? */
	fullnamelen = namelen + strlen(prefix);
	fullname = xmalloc(fullnamelen + 1);
	strcpy(fullname, prefix);
	strcat(fullname, filename);
	pos = cache_name_pos(fullname, fullnamelen);
	if (pos < 0)
		pos = -pos - 1;
	if (pos < active_nr) {
		ce = active_cache[pos];
		if (ce_namelen(ce) == fullnamelen &&
		    !memcmp(ce->name, fullname, fullnamelen))
			die("Path '%s' is in the index, but not '%s'.\n"
			    "Did you mean ':%d:%s' aka ':%d:./%s'?",
			    fullname, filename,
			    ce_stage(ce), fullname,
			    ce_stage(ce), filename);
	}

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in the index.", filename);
	if (errno == ENOENT || errno == ENOTDIR)
		die("Path '%s' does not exist (neither on disk nor in the index).",
		    filename);

	free(fullname);
}