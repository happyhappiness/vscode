static void *preload_thread(void *_data)
{
	int nr;
	struct thread_data *p = _data;
	struct index_state *index = p->index;
	struct cache_entry **cep = index->cache + p->offset;
	struct cache_def cache = CACHE_DEF_INIT;

	nr = p->nr;
	if (nr + p->offset > index->cache_nr)
		nr = index->cache_nr - p->offset;

	do {
		struct cache_entry *ce = *cep++;
		struct stat st;

		if (ce_stage(ce))
			continue;
		if (S_ISGITLINK(ce->ce_mode))
			continue;
		if (ce_uptodate(ce))
			continue;
		if (ce_skip_worktree(ce))
			continue;
		if (!ce_path_match(ce, &p->pathspec, NULL))
			continue;
		if (threaded_has_symlink_leading_path(&cache, ce->name, ce_namelen(ce)))
			continue;
		if (lstat(ce->name, &st))
			continue;
		if (ie_match_stat(index, ce, &st, CE_MATCH_RACY_IS_DIRTY))
			continue;
		ce_mark_uptodate(ce);
	} while (--nr > 0);
	cache_def_clear(&cache);
	return NULL;
}