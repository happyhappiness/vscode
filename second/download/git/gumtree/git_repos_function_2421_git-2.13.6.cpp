void untracked_cache_invalidate_path(struct index_state *istate,
				     const char *path)
{
	if (!istate->untracked || !istate->untracked->root)
		return;
	invalidate_one_component(istate->untracked, istate->untracked->root,
				 path, strlen(path));
}