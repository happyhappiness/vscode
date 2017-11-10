static int lstat_cache_matchlen(struct cache_def *cache,
				const char *name, int len,
				int *ret_flags, int track_flags,
				int prefix_len_stat_func)
{
	int match_len, last_slash, last_slash_dir, previous_slash;
	int save_flags, ret;
	struct stat st;

	if (cache->track_flags != track_flags ||
	    cache->prefix_len_stat_func != prefix_len_stat_func) {
		/*
		 * As a safeguard rule we clear the cache if the
		 * values of track_flags and/or prefix_len_stat_func
		 * does not match with the last supplied values.
		 */
		reset_lstat_cache(cache);
		cache->track_flags = track_flags;
		cache->prefix_len_stat_func = prefix_len_stat_func;
		match_len = last_slash = 0;
	} else {
		/*
		 * Check to see if we have a match from the cache for
		 * the 2 "excluding" path types.
		 */
		match_len = last_slash =
			longest_path_match(name, len, cache->path.buf,
					   cache->path.len, &previous_slash);
		*ret_flags = cache->flags & track_flags & (FL_NOENT|FL_SYMLINK);

		if (!(track_flags & FL_FULLPATH) && match_len == len)
			match_len = last_slash = previous_slash;

		if (*ret_flags && match_len == cache->path.len)
			return match_len;
		/*
		 * If we now have match_len > 0, we would know that
		 * the matched part will always be a directory.
		 *
		 * Also, if we are tracking directories and 'name' is
		 * a substring of the cache on a path component basis,
		 * we can return immediately.
		 */
		*ret_flags = track_flags & FL_DIR;
		if (*ret_flags && len == match_len)
			return match_len;
	}

	/*
	 * Okay, no match from the cache so far, so now we have to
	 * check the rest of the path components.
	 */
	*ret_flags = FL_DIR;
	last_slash_dir = last_slash;
	if (len > cache->path.len)
		strbuf_grow(&cache->path, len - cache->path.len);
	while (match_len < len) {
		do {
			cache->path.buf[match_len] = name[match_len];
			match_len++;
		} while (match_len < len && name[match_len] != '/');
		if (match_len >= len && !(track_flags & FL_FULLPATH))
			break;
		last_slash = match_len;
		cache->path.buf[last_slash] = '\0';

		if (last_slash <= prefix_len_stat_func)
			ret = stat(cache->path.buf, &st);
		else
			ret = lstat(cache->path.buf, &st);

		if (ret) {
			*ret_flags = FL_LSTATERR;
			if (errno == ENOENT)
				*ret_flags |= FL_NOENT;
		} else if (S_ISDIR(st.st_mode)) {
			last_slash_dir = last_slash;
			continue;
		} else if (S_ISLNK(st.st_mode)) {
			*ret_flags = FL_SYMLINK;
		} else {
			*ret_flags = FL_ERR;
		}
		break;
	}

	/*
	 * At the end update the cache.  Note that max 3 different
	 * path types, FL_NOENT, FL_SYMLINK and FL_DIR, can be cached
	 * for the moment!
	 */
	save_flags = *ret_flags & track_flags & (FL_NOENT|FL_SYMLINK);
	if (save_flags && last_slash > 0) {
		cache->path.buf[last_slash] = '\0';
		cache->path.len = last_slash;
		cache->flags = save_flags;
	} else if ((track_flags & FL_DIR) && last_slash_dir > 0) {
		/*
		 * We have a separate test for the directory case,
		 * since it could be that we have found a symlink or a
		 * non-existing directory and the track_flags says
		 * that we cannot cache this fact, so the cache would
		 * then have been left empty in this case.
		 *
		 * But if we are allowed to track real directories, we
		 * can still cache the path components before the last
		 * one (the found symlink or non-existing component).
		 */
		cache->path.buf[last_slash_dir] = '\0';
		cache->path.len = last_slash_dir;
		cache->flags = FL_DIR;
	} else {
		reset_lstat_cache(cache);
	}
	return match_len;
}