static struct cache_entry *refresh_cache_ent(struct index_state *istate,
					     struct cache_entry *ce,
					     unsigned int options, int *err,
					     int *changed_ret)
{
	struct stat st;
	struct cache_entry *updated;
	int changed, size;
	int refresh = options & CE_MATCH_REFRESH;
	int ignore_valid = options & CE_MATCH_IGNORE_VALID;
	int ignore_skip_worktree = options & CE_MATCH_IGNORE_SKIP_WORKTREE;
	int ignore_missing = options & CE_MATCH_IGNORE_MISSING;

	if (!refresh || ce_uptodate(ce))
		return ce;

	/*
	 * CE_VALID or CE_SKIP_WORKTREE means the user promised us
	 * that the change to the work tree does not matter and told
	 * us not to worry.
	 */
	if (!ignore_skip_worktree && ce_skip_worktree(ce)) {
		ce_mark_uptodate(ce);
		return ce;
	}
	if (!ignore_valid && (ce->ce_flags & CE_VALID)) {
		ce_mark_uptodate(ce);
		return ce;
	}

	if (has_symlink_leading_path(ce->name, ce_namelen(ce))) {
		if (ignore_missing)
			return ce;
		if (err)
			*err = ENOENT;
		return NULL;
	}

	if (lstat(ce->name, &st) < 0) {
		if (ignore_missing && errno == ENOENT)
			return ce;
		if (err)
			*err = errno;
		return NULL;
	}

	changed = ie_match_stat(istate, ce, &st, options);
	if (changed_ret)
		*changed_ret = changed;
	if (!changed) {
		/*
		 * The path is unchanged.  If we were told to ignore
		 * valid bit, then we did the actual stat check and
		 * found that the entry is unmodified.  If the entry
		 * is not marked VALID, this is the place to mark it
		 * valid again, under "assume unchanged" mode.
		 */
		if (ignore_valid && assume_unchanged &&
		    !(ce->ce_flags & CE_VALID))
			; /* mark this one VALID again */
		else {
			/*
			 * We do not mark the index itself "modified"
			 * because CE_UPTODATE flag is in-core only;
			 * we are not going to write this change out.
			 */
			if (!S_ISGITLINK(ce->ce_mode))
				ce_mark_uptodate(ce);
			return ce;
		}
	}

	if (ie_modified(istate, ce, &st, options)) {
		if (err)
			*err = EINVAL;
		return NULL;
	}

	size = ce_size(ce);
	updated = xmalloc(size);
	memcpy(updated, ce, size);
	fill_stat_cache_info(updated, &st);
	/*
	 * If ignore_valid is not set, we should leave CE_VALID bit
	 * alone.  Otherwise, paths marked with --no-assume-unchanged
	 * (i.e. things to be edited) will reacquire CE_VALID bit
	 * automatically, which is not really what we want.
	 */
	if (!ignore_valid && assume_unchanged &&
	    !(ce->ce_flags & CE_VALID))
		updated->ce_flags &= ~CE_VALID;

	/* istate->cache_changed is updated in the caller */
	return updated;
}