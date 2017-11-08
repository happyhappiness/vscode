static int icase_exists(struct unpack_trees_options *o, const char *name, int len, struct stat *st)
{
	const struct cache_entry *src;

	src = index_file_exists(o->src_index, name, len, 1);
	return src && !ie_match_stat(o->src_index, src, st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
}