static inline void release_delta_base_cache(struct delta_base_cache_entry *ent)
{
	if (ent->data) {
		free(ent->data);
		ent->data = NULL;
		ent->lru.next->prev = ent->lru.prev;
		ent->lru.prev->next = ent->lru.next;
		delta_base_cached -= ent->size;
	}
}