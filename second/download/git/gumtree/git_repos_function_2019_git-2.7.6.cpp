static int read_cached_dir(struct cached_dir *cdir)
{
	if (cdir->fdir) {
		cdir->de = readdir(cdir->fdir);
		if (!cdir->de)
			return -1;
		return 0;
	}
	while (cdir->nr_dirs < cdir->untracked->dirs_nr) {
		struct untracked_cache_dir *d = cdir->untracked->dirs[cdir->nr_dirs];
		if (!d->recurse) {
			cdir->nr_dirs++;
			continue;
		}
		cdir->ucd = d;
		cdir->nr_dirs++;
		return 0;
	}
	cdir->ucd = NULL;
	if (cdir->nr_files < cdir->untracked->untracked_nr) {
		struct untracked_cache_dir *d = cdir->untracked;
		cdir->file = d->untracked[cdir->nr_files++];
		return 0;
	}
	return -1;
}