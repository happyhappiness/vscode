void clear_delta_base_cache(void)
{
	struct list_head *lru, *tmp;
	list_for_each_safe(lru, tmp, &delta_base_cache_lru) {
		struct delta_base_cache_entry *entry =
			list_entry(lru, struct delta_base_cache_entry, lru);
		release_delta_base_cache(entry);
	}
}