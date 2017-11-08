static void diagnose_invalid_index_path(int stage,
					const char *prefix,
					const char *filename)
{
	const struct cache_entry *ce;
	int pos;
	unsigned namelen = strlen(filename);
	struct strbuf fullname = STRBUF_INIT;

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
	strbuf_addstr(&fullname, prefix);
	strbuf_addstr(&fullname, filename);
	pos = cache_name_pos(fullname.buf, fullname.len);
	if (pos < 0)
		pos = -pos - 1;
	if (pos < active_nr) {
		ce = active_cache[pos];
		if (ce_namelen(ce) == fullname.len &&
		    !memcmp(ce->name, fullname.buf, fullname.len))
			die("Path '%s' is in the index, but not '%s'.\n"
			    "Did you mean ':%d:%s' aka ':%d:./%s'?",
			    fullname.buf, filename,
			    ce_stage(ce), fullname.buf,
			    ce_stage(ce), filename);
	}

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in the index.", filename);
	if (errno == ENOENT || errno == ENOTDIR)
		die("Path '%s' does not exist (neither on disk nor in the index).",
		    filename);

	strbuf_release(&fullname);
}