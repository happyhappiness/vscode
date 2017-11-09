static void prune_index(struct index_state *istate,
			const char *prefix, size_t prefixlen)
{
	int pos;
	unsigned int first, last;

	if (!prefix || !istate->cache_nr)
		return;
	pos = index_name_pos(istate, prefix, prefixlen);
	if (pos < 0)
		pos = -pos-1;
	first = pos;
	last = istate->cache_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		const struct cache_entry *ce = istate->cache[next];
		if (!strncmp(ce->name, prefix, prefixlen)) {
			first = next+1;
			continue;
		}
		last = next;
	}
	MOVE_ARRAY(istate->cache, istate->cache + pos, last - pos);
	istate->cache_nr = last - pos;
}