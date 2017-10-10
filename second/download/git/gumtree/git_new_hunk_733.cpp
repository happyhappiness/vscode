		die("BUG: peel called before advance for cache iterator");

	entry = level->dir->entries[level->index];

	if (peel_entry(entry, 0))
		return -1;
	oidcpy(peeled, &entry->u.value.peeled);
	return 0;
}

static int cache_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct cache_ref_iterator *iter =
