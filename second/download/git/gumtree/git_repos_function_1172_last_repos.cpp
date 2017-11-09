int oidset_contains(const struct oidset *set, const struct object_id *oid)
{
	struct hashmap_entry key;

	if (!set->map.cmpfn)
		return 0;

	hashmap_entry_init(&key, sha1hash(oid->hash));
	return !!hashmap_get(&set->map, &key, oid);
}