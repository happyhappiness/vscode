static int verify_index_match(const struct cache_entry *ce, struct stat *st)
{
	if (S_ISGITLINK(ce->ce_mode)) {
		if (!S_ISDIR(st->st_mode))
			return -1;
		return 0;
	}
	return ce_match_stat(ce, st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
}