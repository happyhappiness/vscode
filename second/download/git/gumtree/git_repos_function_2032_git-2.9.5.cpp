static void invalidate_gitignore(struct untracked_cache *uc,
				 struct untracked_cache_dir *dir)
{
	uc->gitignore_invalidated++;
	do_invalidate_gitignore(dir);
}