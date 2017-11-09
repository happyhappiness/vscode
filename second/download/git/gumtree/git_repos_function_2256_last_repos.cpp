static inline void release_delta_base_cache(struct delta_base_cache_entry *ent)
{
	free(ent->data);
	detach_delta_base_cache_entry(ent);
}