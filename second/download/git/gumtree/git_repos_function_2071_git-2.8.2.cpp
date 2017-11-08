void free_untracked_cache(struct untracked_cache *uc)
{
	if (uc)
		free_untracked(uc->root);
	free(uc);
}