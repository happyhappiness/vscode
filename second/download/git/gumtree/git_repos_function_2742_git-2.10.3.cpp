static int do_compare_entry(const struct cache_entry *ce,
			    const struct traverse_info *info,
			    const struct name_entry *n)
{
	int len, pathlen, ce_len;
	const char *ce_name;
	int cmp;

	/*
	 * If we have not precomputed the traverse path, it is quicker
	 * to avoid doing so.  But if we have precomputed it,
	 * it is quicker to use the precomputed version.
	 */
	if (!info->traverse_path)
		return do_compare_entry_piecewise(ce, info, n);

	cmp = strncmp(ce->name, info->traverse_path, info->pathlen);
	if (cmp)
		return cmp;

	pathlen = info->pathlen;
	ce_len = ce_namelen(ce);

	if (ce_len < pathlen)
		return -1;

	ce_len -= pathlen;
	ce_name = ce->name + pathlen;

	len = tree_entry_len(n);
	return df_name_compare(ce_name, ce_len, S_IFREG, n->path, len, n->mode);
}