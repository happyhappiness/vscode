static void merge_all(void)
{
	int i;
	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];
		if (!ce_stage(ce))
			continue;
		i += merge_entry(i, ce->name)-1;
	}
}