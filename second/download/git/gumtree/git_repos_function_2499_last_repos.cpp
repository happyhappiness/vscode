static int valid_cached_dir(struct dir_struct *dir,
			    struct untracked_cache_dir *untracked,
			    struct index_state *istate,
			    struct strbuf *path,
			    int check_only)
{
	struct stat st;

	if (!untracked)
		return 0;

	if (stat(path->len ? path->buf : ".", &st)) {
		invalidate_directory(dir->untracked, untracked);
		memset(&untracked->stat_data, 0, sizeof(untracked->stat_data));
		return 0;
	}
	if (!untracked->valid ||
	    match_stat_data_racy(istate, &untracked->stat_data, &st)) {
		if (untracked->valid)
			invalidate_directory(dir->untracked, untracked);
		fill_stat_data(&untracked->stat_data, &st);
		return 0;
	}

	if (untracked->check_only != !!check_only) {
		invalidate_directory(dir->untracked, untracked);
		return 0;
	}

	/*
	 * prep_exclude will be called eventually on this directory,
	 * but it's called much later in last_exclude_matching(). We
	 * need it now to determine the validity of the cache for this
	 * path. The next calls will be nearly no-op, the way
	 * prep_exclude() is designed.
	 */
	if (path->len && path->buf[path->len - 1] != '/') {
		strbuf_addch(path, '/');
		prep_exclude(dir, istate, path->buf, path->len);
		strbuf_setlen(path, path->len - 1);
	} else
		prep_exclude(dir, istate, path->buf, path->len);

	/* hopefully prep_exclude() haven't invalidated this entry... */
	return untracked->valid;
}