static void free_untracked(struct untracked_cache_dir *ucd)
{
	int i;
	if (!ucd)
		return;
	for (i = 0; i < ucd->dirs_nr; i++)
		free_untracked(ucd->dirs[i]);
	for (i = 0; i < ucd->untracked_nr; i++)
		free(ucd->untracked[i]);
	free(ucd->untracked);
	free(ucd->dirs);
	free(ucd);
}