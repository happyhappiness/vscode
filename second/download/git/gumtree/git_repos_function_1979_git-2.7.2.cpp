static void do_invalidate_gitignore(struct untracked_cache_dir *dir)
{
	int i;
	dir->valid = 0;
	dir->untracked_nr = 0;
	for (i = 0; i < dir->dirs_nr; i++)
		do_invalidate_gitignore(dir->dirs[i]);
}