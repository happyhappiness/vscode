static int cache_ref_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;
	struct cache_ref_iterator_level *level;
	struct ref_entry *entry;

	level = &iter->levels[iter->levels_nr - 1];

	if (level->index == -1)
		die("BUG: peel called before advance for cache iterator");

	entry = level->dir->entries[level->index];

	if (peel_entry(entry, 0))
		return -1;
	oidcpy(peeled, &entry->u.value.peeled);
	return 0;
}