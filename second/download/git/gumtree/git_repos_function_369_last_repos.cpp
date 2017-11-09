static void post_read_index_from(struct index_state *istate)
{
	check_ce_order(istate);
	tweak_untracked_cache(istate);
	tweak_split_index(istate);
}