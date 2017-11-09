static int is_racy_timestamp(const struct index_state *istate,
			     const struct cache_entry *ce)
{
	return (!S_ISGITLINK(ce->ce_mode) &&
		is_racy_stat(istate, &ce->ce_stat_data));
}