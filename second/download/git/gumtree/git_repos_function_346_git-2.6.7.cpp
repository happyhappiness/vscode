int unmerged_index(const struct index_state *istate)
{
	int i;
	for (i = 0; i < istate->cache_nr; i++) {
		if (ce_stage(istate->cache[i]))
			return 1;
	}
	return 0;
}