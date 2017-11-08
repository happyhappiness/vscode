int remove_file_from_index(struct index_state *istate, const char *path)
{
	int pos = index_name_pos(istate, path, strlen(path));
	if (pos < 0)
		pos = -pos-1;
	cache_tree_invalidate_path(istate, path);
	untracked_cache_remove_from_index(istate, path);
	while (pos < istate->cache_nr && !strcmp(istate->cache[pos]->name, path))
		remove_index_entry_at(istate, pos);
	return 0;
}