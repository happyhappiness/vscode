static void add_delta_base_cache(struct packed_git *p, off_t base_offset,
	void *base, unsigned long base_size, enum object_type type)
{
	unsigned long hash = pack_entry_hash(p, base_offset);
	struct delta_base_cache_entry *ent = delta_base_cache + hash;
	struct delta_base_cache_lru_list *lru;

	release_delta_base_cache(ent);
	delta_base_cached += base_size;

	for (lru = delta_base_cache_lru.next;
	     delta_base_cached > delta_base_cache_limit
	     && lru != &delta_base_cache_lru;
	     lru = lru->next) {
		struct delta_base_cache_entry *f = (void *)lru;
		if (f->type == OBJ_BLOB)
			release_delta_base_cache(f);
	}
	for (lru = delta_base_cache_lru.next;
	     delta_base_cached > delta_base_cache_limit
	     && lru != &delta_base_cache_lru;
	     lru = lru->next) {
		struct delta_base_cache_entry *f = (void *)lru;
		release_delta_base_cache(f);
	}

	ent->p = p;
	ent->base_offset = base_offset;
	ent->type = type;
	ent->data = base;
	ent->size = base_size;
	ent->lru.next = &delta_base_cache_lru;
	ent->lru.prev = delta_base_cache_lru.prev;
	delta_base_cache_lru.prev->next = &ent->lru;
	delta_base_cache_lru.prev = &ent->lru;
}