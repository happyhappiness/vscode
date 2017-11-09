static void invalidate_directory(struct untracked_cache *uc,
				 struct untracked_cache_dir *dir)
{
	int i;
	uc->dir_invalidated++;
	dir->valid = 0;
	dir->untracked_nr = 0;
	for (i = 0; i < dir->dirs_nr; i++)
		dir->dirs[i]->recurse = 0;
}