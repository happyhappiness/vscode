(le = res->buckets[bucket]; le != NULL; le = le->next) {
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