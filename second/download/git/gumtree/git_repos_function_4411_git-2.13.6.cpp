const void *memintern(const void *data, size_t len)
{
	static struct hashmap map;
	struct pool_entry key, *e;

	/* initialize string pool hashmap */
	if (!map.tablesize)
		hashmap_init(&map, (hashmap_cmp_fn) pool_entry_cmp, 0);

	/* lookup interned string in pool */
	hashmap_entry_init(&key, memhash(data, len));
	key.len = len;
	e = hashmap_get(&map, &key, data);
	if (!e) {
		/* not found: create it */
		FLEX_ALLOC_MEM(e, data, data, len);
		hashmap_entry_init(e, key.ent.hash);
		e->len = len;
		hashmap_add(&map, e);
	}
	return e->data;
}