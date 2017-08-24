{
	struct links_entry *le;
	size_t hash, bucket;

	/* Add this entry to the links cache. */
	le = calloc(1, sizeof(struct links_entry));
	if (le == NULL)
		return (NULL);
	le->canonical = archive_entry_clone(entry);

	/* If the links cache is getting too full, enlarge the hash table. */
	if (res->number_entries > res->number_buckets * 2)
		grow_hash(res);

	hash = (size_t)(archive_entry_dev(entry) ^ archive_entry_ino64(entry));
	bucket = hash & (res->number_buckets - 1);

	/* If we could allocate the entry, record it. */
	if (res->buckets[bucket] != NULL)
		res->buckets[bucket]->previous = le;
	res->number_entries++;
	le->next = res->buckets[bucket];
	le->previous = NULL;
	res->buckets[bucket] = le;
	le->hash = hash;
	le->links = archive_entry_nlink(entry) - 1;
	return (le);
}