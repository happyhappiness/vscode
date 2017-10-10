			continue;

		if (!entry->preferred_base) {
			nr_deltas++;
			if (entry->type < 0)
				die("unable to get type of object %s",
				    oid_to_hex(&entry->idx.oid));
		} else {
			if (entry->type < 0) {
				/*
				 * This object is not found, but we
				 * don't have to include it anyway.
				 */
