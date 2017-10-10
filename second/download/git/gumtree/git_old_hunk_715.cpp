
void untracked_cache_add_to_index(struct index_state *istate,
				  const char *path)
{
	untracked_cache_invalidate_path(istate, path);
}
