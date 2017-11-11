void remove_untracked_cache(struct index_state *istate)
{
	if (istate->untracked) {
		free_untracked_cache(istate->untracked);
		istate->untracked = NULL;
		istate->cache_changed |= UNTRACKED_CHANGED;
	}
}