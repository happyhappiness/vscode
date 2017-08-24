{
			/* Remove entry from old bucket. */
			le = res->buckets[i];
			res->buckets[i] = le->next;

			/* Add entry to new bucket. */
			bucket = le->hash & (new_size - 1);

			if (new_buckets[bucket] != NULL)
				new_buckets[bucket]->previous = le;
			le->next = new_buckets[bucket];
			le->previous = NULL;
			new_buckets[bucket] = le;
		}