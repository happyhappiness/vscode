static int mark_ce_flags(const char *path, int flag, int mark)
{
	int namelen = strlen(path);
	int pos = cache_name_pos(path, namelen);
	if (0 <= pos) {
		if (mark)
			active_cache[pos]->ce_flags |= flag;
		else
			active_cache[pos]->ce_flags &= ~flag;
		cache_tree_invalidate_path(active_cache_tree, path);
		active_cache_changed = 1;
		return 0;
	}
	return -1;
}