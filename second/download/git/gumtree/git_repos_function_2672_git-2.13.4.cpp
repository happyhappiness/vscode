static inline void hashmap_disallow_rehash(struct hashmap *map, unsigned value)
{
	map->disallow_rehash = value;
}