static int update_stages(struct merge_options *opt, const char *path,
			 const struct diff_filespec *o,
			 const struct diff_filespec *a,
			 const struct diff_filespec *b)
{

	/*
	 * NOTE: It is usually a bad idea to call update_stages on a path
	 * before calling update_file on that same path, since it can
	 * sometimes lead to spurious "refusing to lose untracked file..."
	 * messages from update_file (via make_room_for path via
	 * would_lose_untracked).  Instead, reverse the order of the calls
	 * (executing update_file first and then update_stages).
	 */
	int clear = 1;
	int options = ADD_CACHE_OK_TO_ADD | ADD_CACHE_SKIP_DFCHECK;
	if (clear)
		if (remove_file_from_cache(path))
			return -1;
	if (o)
		if (add_cacheinfo(opt, o->mode, &o->oid, path, 1, 0, options))
			return -1;
	if (a)
		if (add_cacheinfo(opt, a->mode, &a->oid, path, 2, 0, options))
			return -1;
	if (b)
		if (add_cacheinfo(opt, b->mode, &b->oid, path, 3, 0, options))
			return -1;
	return 0;
}