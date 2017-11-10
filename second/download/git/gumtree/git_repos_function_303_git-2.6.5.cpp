int ie_modified(const struct index_state *istate,
		const struct cache_entry *ce,
		struct stat *st, unsigned int options)
{
	int changed, changed_fs;

	changed = ie_match_stat(istate, ce, st, options);
	if (!changed)
		return 0;
	/*
	 * If the mode or type has changed, there's no point in trying
	 * to refresh the entry - it's not going to match
	 */
	if (changed & (MODE_CHANGED | TYPE_CHANGED))
		return changed;

	/*
	 * Immediately after read-tree or update-index --cacheinfo,
	 * the length field is zero, as we have never even read the
	 * lstat(2) information once, and we cannot trust DATA_CHANGED
	 * returned by ie_match_stat() which in turn was returned by
	 * ce_match_stat_basic() to signal that the filesize of the
	 * blob changed.  We have to actually go to the filesystem to
	 * see if the contents match, and if so, should answer "unchanged".
	 *
	 * The logic does not apply to gitlinks, as ce_match_stat_basic()
	 * already has checked the actual HEAD from the filesystem in the
	 * subproject.  If ie_match_stat() already said it is different,
	 * then we know it is.
	 */
	if ((changed & DATA_CHANGED) &&
	    (S_ISGITLINK(ce->ce_mode) || ce->ce_stat_data.sd_size != 0))
		return changed;

	changed_fs = ce_modified_check_fs(ce, st);
	if (changed_fs)
		return changed | changed_fs;
	return 0;
}