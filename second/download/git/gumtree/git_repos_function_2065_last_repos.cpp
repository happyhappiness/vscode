void unmerge_index(struct index_state *istate, const struct pathspec *pathspec)
{
	int i;

	if (!istate->resolve_undo)
		return;

	for (i = 0; i < istate->cache_nr; i++) {
		const struct cache_entry *ce = istate->cache[i];
		if (!ce_path_match(ce, pathspec, NULL))
			continue;
		i = unmerge_index_entry_at(istate, i);
	}
}