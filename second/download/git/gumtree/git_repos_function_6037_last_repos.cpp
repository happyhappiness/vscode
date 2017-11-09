static int mark_ce_flags(const char *path, int flag, int mark)
{
	int namelen = strlen(path);
	int pos = cache_name_pos(path, namelen);
	if (0 <= pos) {
		if (mark)
			active_cache[pos]->ce_flags |= flag;
		else
			active_cache[pos]->ce_flags &= ~flag;
		active_cache[pos]->ce_flags |= CE_UPDATE_IN_BASE;
		cache_tree_invalidate_path(&the_index, path);
		active_cache_changed |= CE_ENTRY_CHANGED;
		return 0;
	}
	return -1;
}