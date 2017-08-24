(le = res->buckets[bucket]; le != NULL; le = le->next) {
			if (le->entry != NULL &&
			    (mode & NEXT_ENTRY_DEFERRED) == 0)
				continue;
			if (le->entry == NULL &&
			    (mode & NEXT_ENTRY_PARTIAL) == 0)
				continue;
			/* Remove it from this hash bucket. */
			if (le->next != NULL)
				le->next->previous = le->previous;
			if (le->previous != NULL)
				le->previous->next = le->next;
			else
				res->buckets[bucket] = le->next;
			res->number_entries--;
			/* Defer freeing this entry. */
			res->spare = le;
			return (le);
		}