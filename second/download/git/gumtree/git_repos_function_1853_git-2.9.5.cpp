static void clear_delta_base_cache_entry(struct delta_base_cache_entry *ent)
{
	ent->data = NULL;
	ent->lru.next->prev = ent->lru.prev;
	ent->lru.prev->next = ent->lru.next;
	delta_base_cached -= ent->size;
}