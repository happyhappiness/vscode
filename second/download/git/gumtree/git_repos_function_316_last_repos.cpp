void fill_stat_cache_info(struct cache_entry *ce, struct stat *st)
{
	fill_stat_data(&ce->ce_stat_data, st);

	if (assume_unchanged)
		ce->ce_flags |= CE_VALID;

	if (S_ISREG(st->st_mode))
		ce_mark_uptodate(ce);
}