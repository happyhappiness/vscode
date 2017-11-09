void rename_index_entry_at(struct index_state *istate, int nr, const char *new_name)
{
	struct cache_entry *old = istate->cache[nr], *new;
	int namelen = strlen(new_name);

	new = xmalloc(cache_entry_size(namelen));
	copy_cache_entry(new, old);
	new->ce_flags &= ~CE_HASHED;
	new->ce_namelen = namelen;
	new->index = 0;
	memcpy(new->name, new_name, namelen + 1);

	cache_tree_invalidate_path(istate, old->name);
	untracked_cache_remove_from_index(istate, old->name);
	remove_index_entry_at(istate, nr);
	add_index_entry(istate, new, ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE);
}