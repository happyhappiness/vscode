void *hashmap_get_next(const struct hashmap *map, const void *entry)
{
	struct hashmap_entry *e = ((struct hashmap_entry *) entry)->next;
	for (; e; e = e->next)
		if (entry_equals(map, entry, e, NULL))
			return e;
	return NULL;
}