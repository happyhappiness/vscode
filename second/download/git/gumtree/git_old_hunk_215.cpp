
unmap:
	munmap(mmap, mmap_size);
	die("index file corrupt");
}

int is_index_unborn(struct index_state *istate)
{
	return (!istate->cache_nr && !istate->timestamp.sec);
}

int discard_index(struct index_state *istate)
{
	int i;

	for (i = 0; i < istate->cache_nr; i++)
		free(istate->cache[i]);
	resolve_undo_clear_index(istate);
	istate->cache_nr = 0;
	istate->cache_changed = 0;
	istate->timestamp.sec = 0;
	istate->timestamp.nsec = 0;
	free_name_hash(istate);
	cache_tree_free(&(istate->cache_tree));
	istate->initialized = 0;
	free(istate->cache);
	istate->cache = NULL;
	istate->cache_alloc = 0;
	return 0;
}

int unmerged_index(const struct index_state *istate)
{
	int i;
