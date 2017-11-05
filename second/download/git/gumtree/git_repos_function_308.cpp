static int index_name_stage_pos(const struct index_state *istate, const char *name, int namelen, int stage)
{
	int first, last;

	first = 0;
	last = istate->cache_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		struct cache_entry *ce = istate->cache[next];
		int cmp = cache_name_stage_compare(name, namelen, stage, ce->name, ce_namelen(ce), ce_stage(ce));
		if (!cmp)
			return next;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}
	return -first-1;
}