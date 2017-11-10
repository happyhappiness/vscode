static int add_index_entry_with_check(struct index_state *istate, struct cache_entry *ce, int option)
{
	int pos;
	int ok_to_add = option & ADD_CACHE_OK_TO_ADD;
	int ok_to_replace = option & ADD_CACHE_OK_TO_REPLACE;
	int skip_df_check = option & ADD_CACHE_SKIP_DFCHECK;
	int new_only = option & ADD_CACHE_NEW_ONLY;

	if (!(option & ADD_CACHE_KEEP_CACHE_TREE))
		cache_tree_invalidate_path(istate, ce->name);
	pos = index_name_stage_pos(istate, ce->name, ce_namelen(ce), ce_stage(ce));

	/* existing match? Just replace it. */
	if (pos >= 0) {
		if (!new_only)
			replace_index_entry(istate, pos, ce);
		return 0;
	}
	pos = -pos-1;

	/*
	 * Inserting a merged entry ("stage 0") into the index
	 * will always replace all non-merged entries..
	 */
	if (pos < istate->cache_nr && ce_stage(ce) == 0) {
		while (ce_same_name(istate->cache[pos], ce)) {
			ok_to_add = 1;
			if (!remove_index_entry_at(istate, pos))
				break;
		}
	}

	if (!ok_to_add)
		return -1;
	if (!verify_path(ce->name))
		return error("Invalid path '%s'", ce->name);

	if (!skip_df_check &&
	    check_file_directory_conflict(istate, ce, pos, ok_to_replace)) {
		if (!ok_to_replace)
			return error("'%s' appears as both a file and as a directory",
				     ce->name);
		pos = index_name_stage_pos(istate, ce->name, ce_namelen(ce), ce_stage(ce));
		pos = -pos-1;
	}
	return pos + 1;
}