void clear_delta_base_cache(void)
{
	struct hashmap_iter iter;
	struct delta_base_cache_entry *entry;
	for (entry = hashmap_iter_first(&delta_base_cache, &iter);
	     entry;
	     entry = hashmap_iter_next(&iter)) {
		release_delta_base_cache(entry);
	}
}