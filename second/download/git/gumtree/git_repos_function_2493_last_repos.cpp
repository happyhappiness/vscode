static int get_index_dtype(struct index_state *istate,
			   const char *path, int len)
{
	int pos;
	const struct cache_entry *ce;

	ce = index_file_exists(istate, path, len, 0);
	if (ce) {
		if (!ce_uptodate(ce))
			return DT_UNKNOWN;
		if (S_ISGITLINK(ce->ce_mode))
			return DT_DIR;
		/*
		 * Nobody actually cares about the
		 * difference between DT_LNK and DT_REG
		 */
		return DT_REG;
	}

	/* Try to look it up as a directory */
	pos = index_name_pos(istate, path, len);
	if (pos >= 0)
		return DT_UNKNOWN;
	pos = -pos-1;
	while (pos < istate->cache_nr) {
		ce = istate->cache[pos++];
		if (strncmp(ce->name, path, len))
			break;
		if (ce->name[len] > '/')
			break;
		if (ce->name[len] < '/')
			continue;
		if (!ce_uptodate(ce))
			break;	/* continue? */
		return DT_DIR;
	}
	return DT_UNKNOWN;
}