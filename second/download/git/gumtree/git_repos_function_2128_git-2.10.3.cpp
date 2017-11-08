void untracked_cache_remove_from_index(struct index_state *istate,
				       const char *path)
{
	untracked_cache_invalidate_path(istate, path);
}