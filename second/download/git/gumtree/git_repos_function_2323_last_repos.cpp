static void attr_hashmap_init(struct attr_hashmap *map)
{
	hashmap_init(&map->map, (hashmap_cmp_fn) attr_hash_entry_cmp, NULL, 0);
}