void *hashmap_get(const struct hashmap *map, const void *key, const void *keydata)
{
	return *find_entry_ptr(map, key, keydata);
}