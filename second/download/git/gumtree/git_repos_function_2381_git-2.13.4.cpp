static void add_untracked(struct untracked_cache_dir *dir, const char *name)
{
	if (!dir)
		return;
	ALLOC_GROW(dir->untracked, dir->untracked_nr + 1,
		   dir->untracked_alloc);
	dir->untracked[dir->untracked_nr++] = xstrdup(name);
}