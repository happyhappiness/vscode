static void prune_cache(const char *prefix)
{
	int pos = cache_name_pos(prefix, max_prefix_len);
	unsigned int first, last;

	if (pos < 0)
		pos = -pos-1;
	memmove(active_cache, active_cache + pos,
		(active_nr - pos) * sizeof(struct cache_entry *));
	active_nr -= pos;
	first = 0;
	last = active_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		const struct cache_entry *ce = active_cache[next];
		if (!strncmp(ce->name, prefix, max_prefix_len)) {
			first = next+1;
			continue;
		}
		last = next;
	}
	active_nr = last;
}