{
	struct links_entry	*le;
	size_t			 hash, bucket;
	dev_t			 dev;
	int64_t			 ino;

	/* Free a held entry. */
	if (res->spare != NULL) {
		archive_entry_free(res->spare->canonical);
		archive_entry_free(res->spare->entry);
		free(res->spare);
		res->spare = NULL;
	}

	dev = archive_entry_dev(entry);
	ino = archive_entry_ino64(entry);
	hash = (size_t)(dev ^ ino);

	/* Try to locate this entry in the links cache. */
	bucket = hash & (res->number_buckets - 1);
	for (le = res->buckets[bucket]; le != NULL; le = le->next) {
		if (le->hash == hash
		    && dev == archive_entry_dev(le->canonical)
		    && ino == archive_entry_ino64(le->canonical)) {
			/*
			 * Decrement link count each time and release
			 * the entry if it hits zero.  This saves
			 * memory and is necessary for detecting
			 * missed links.
			 */
			--le->links;
			if (le->links > 0)
				return (le);
			/* Remove it from this hash bucket. */
			if (le->previous != NULL)
				le->previous->next = le->next;
			if (le->next != NULL)
				le->next->previous = le->previous;
			if (res->buckets[bucket] == le)
				res->buckets[bucket] = le->next;
			res->number_entries--;
			/* Defer freeing this entry. */
			res->spare = le;
			return (le);
		}
	}
	return (NULL);
}