static int match_pathspec_item(const struct pathspec_item *item, int prefix,
			       const char *name, int namelen, unsigned flags)
{
	/* name/namelen has prefix cut off by caller */
	const char *match = item->match + prefix;
	int matchlen = item->len - prefix;

	/*
	 * The normal call pattern is:
	 * 1. prefix = common_prefix_len(ps);
	 * 2. prune something, or fill_directory
	 * 3. match_pathspec()
	 *
	 * 'prefix' at #1 may be shorter than the command's prefix and
	 * it's ok for #2 to match extra files. Those extras will be
	 * trimmed at #3.
	 *
	 * Suppose the pathspec is 'foo' and '../bar' running from
	 * subdir 'xyz'. The common prefix at #1 will be empty, thanks
	 * to "../". We may have xyz/foo _and_ XYZ/foo after #2. The
	 * user does not want XYZ/foo, only the "foo" part should be
	 * case-insensitive. We need to filter out XYZ/foo here. In
	 * other words, we do not trust the caller on comparing the
	 * prefix part when :(icase) is involved. We do exact
	 * comparison ourselves.
	 *
	 * Normally the caller (common_prefix_len() in fact) does
	 * _exact_ matching on name[-prefix+1..-1] and we do not need
	 * to check that part. Be defensive and check it anyway, in
	 * case common_prefix_len is changed, or a new caller is
	 * introduced that does not use common_prefix_len.
	 *
	 * If the penalty turns out too high when prefix is really
	 * long, maybe change it to
	 * strncmp(match, name, item->prefix - prefix)
	 */
	if (item->prefix && (item->magic & PATHSPEC_ICASE) &&
	    strncmp(item->match, name - prefix, item->prefix))
		return 0;

	/* If the match was just the prefix, we matched */
	if (!*match)
		return MATCHED_RECURSIVELY;

	if (matchlen <= namelen && !ps_strncmp(item, match, name, matchlen)) {
		if (matchlen == namelen)
			return MATCHED_EXACTLY;

		if (match[matchlen-1] == '/' || name[matchlen] == '/')
			return MATCHED_RECURSIVELY;
	} else if ((flags & DO_MATCH_DIRECTORY) &&
		   match[matchlen - 1] == '/' &&
		   namelen == matchlen - 1 &&
		   !ps_strncmp(item, match, name, namelen))
		return MATCHED_EXACTLY;

	if (item->nowildcard_len < item->len &&
	    !git_fnmatch(item, match, name,
			 item->nowildcard_len - prefix))
		return MATCHED_FNMATCH;

	return 0;
}