static int skip_same_name(const struct cache_entry *ce, int pos)
{
	while (++pos < active_nr &&
	       !strcmp(active_cache[pos]->name, ce->name))
		; /* skip */
	return pos;
}