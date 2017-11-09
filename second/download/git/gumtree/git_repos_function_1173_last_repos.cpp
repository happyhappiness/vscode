int oidset_insert(struct oidset *set, const struct object_id *oid)
{
	struct oidset_entry *entry;

	if (!set->map.cmpfn)
		hashmap_init(&set->map, oidset_hashcmp, NULL, 0);

	if (oidset_contains(set, oid))
		return 1;

	entry = xmalloc(sizeof(*entry));
	hashmap_entry_init(&entry->hash, sha1hash(oid->hash));
	oidcpy(&entry->oid, oid);

	hashmap_add(&set->map, entry);
	return 0;
}