{
	const char *name;
	int slot;


	cache->probes++;

	slot = id % cache->size;
	if (cache->cache[slot].name != NULL) {
		if (cache->cache[slot].id == id) {
			cache->hits++;
			if (cache->cache[slot].name == NO_NAME)
				return (NULL);
			return (cache->cache[slot].name);
		}
		if (cache->cache[slot].name != NO_NAME)
			free((void *)(uintptr_t)cache->cache[slot].name);
		cache->cache[slot].name = NULL;
	}

	name = (lookup_fn)(cache, id);
	if (name == NULL) {
		/* Cache and return the negative response. */
		cache->cache[slot].name = NO_NAME;
		cache->cache[slot].id = id;
		return (NULL);
	}

	cache->cache[slot].name = name;
	cache->cache[slot].id = id;
	return (cache->cache[slot].name);
}