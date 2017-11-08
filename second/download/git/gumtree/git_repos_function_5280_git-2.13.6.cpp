static void prune_cache(const char *prefix, size_t prefixlen)
{
	int pos;
	unsigned int first, last;

	if (!prefix)
		return;
	pos = cache_name_pos(prefix, prefixlen);
	if (pos < 0)
		pos = -pos-1;
	first = pos;
	last = active_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		const struct cache_entry *ce = active_cache[next];
		if (!strncmp(ce->name, prefix, prefixlen)) {
			first = next+1;
			continue;
		}
		last = next;
	}
	memmove(active_cache, active_cache + pos,
		(last - pos) * sizeof(struct cache_entry *));
	active_nr = last - pos;
}