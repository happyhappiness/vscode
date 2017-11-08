int is_index_unborn(struct index_state *istate)
{
	return (!istate->cache_nr && !istate->timestamp.sec);
}