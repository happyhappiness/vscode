static int open_cached_dir(struct cached_dir *cdir,
			   struct dir_struct *dir,
			   struct untracked_cache_dir *untracked,
			   struct index_state *istate,
			   struct strbuf *path,
			   int check_only)
{
	memset(cdir, 0, sizeof(*cdir));
	cdir->untracked = untracked;
	if (valid_cached_dir(dir, untracked, istate, path, check_only))
		return 0;
	cdir->fdir = opendir(path->len ? path->buf : ".");
	if (dir->untracked)
		dir->untracked->dir_opened++;
	if (!cdir->fdir)
		return -1;
	return 0;
}