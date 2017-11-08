struct delta_index * create_delta_index(const void *buf, unsigned long bufsize)
{
	unsigned int i, hsize, hmask, entries, prev_val, *hash_count;
	const unsigned char *data, *buffer = buf;
	struct delta_index *index;
	struct unpacked_index_entry *entry, **hash;
	struct index_entry *packed_entry, **packed_hash;
	void *mem;
	unsigned long memsize;

	if (!buf || !bufsize)
		return NULL;

	/* Determine index hash size.  Note that indexing skips the
	   first byte to allow for optimizing the Rabin's polynomial
	   initialization in create_delta(). */
	entries = (bufsize - 1) / RABIN_WINDOW;
	if (bufsize >= 0xffffffffUL) {
		/*
		 * Current delta format can't encode offsets into
		 * reference buffer with more than 32 bits.
		 */
		entries = 0xfffffffeU / RABIN_WINDOW;
	}
	hsize = entries / 4;
	for (i = 4; (1u << i) < hsize; i++);
	hsize = 1 << i;
	hmask = hsize - 1;

	/* allocate lookup index */
	memsize = sizeof(*hash) * hsize +
		  sizeof(*entry) * entries;
	mem = malloc(memsize);
	if (!mem)
		return NULL;
	hash = mem;
	mem = hash + hsize;
	entry = mem;

	memset(hash, 0, hsize * sizeof(*hash));

	/* allocate an array to count hash entries */
	hash_count = calloc(hsize, sizeof(*hash_count));
	if (!hash_count) {
		free(hash);
		return NULL;
	}

	/* then populate the index */
	prev_val = ~0;
	for (data = buffer + entries * RABIN_WINDOW - RABIN_WINDOW;
	     data >= buffer;
	     data -= RABIN_WINDOW) {
		unsigned int val = 0;
		for (i = 1; i <= RABIN_WINDOW; i++)
			val = ((val << 8) | data[i]) ^ T[val >> RABIN_SHIFT];
		if (val == prev_val) {
			/* keep the lowest of consecutive identical blocks */
			entry[-1].entry.ptr = data + RABIN_WINDOW;
			--entries;
		} else {
			prev_val = val;
			i = val & hmask;
			entry->entry.ptr = data + RABIN_WINDOW;
			entry->entry.val = val;
			entry->next = hash[i];
			hash[i] = entry++;
			hash_count[i]++;
		}
	}

	/*
	 * Determine a limit on the number of entries in the same hash
	 * bucket.  This guards us against pathological data sets causing
	 * really bad hash distribution with most entries in the same hash
	 * bucket that would bring us to O(m*n) computing costs (m and n
	 * corresponding to reference and target buffer sizes).
	 *
	 * Make sure none of the hash buckets has more entries than
	 * we're willing to test.  Otherwise we cull the entry list
	 * uniformly to still preserve a good repartition across
	 * the reference buffer.
	 */
	for (i = 0; i < hsize; i++) {
		int acc;

		if (hash_count[i] <= HASH_LIMIT)
			continue;

		/* We leave exactly HASH_LIMIT entries in the bucket */
		entries -= hash_count[i] - HASH_LIMIT;

		entry = hash[i];
		acc = 0;

		/*
		 * Assume that this loop is gone through exactly
		 * HASH_LIMIT times and is entered and left with
		 * acc==0.  So the first statement in the loop
		 * contributes (hash_count[i]-HASH_LIMIT)*HASH_LIMIT
		 * to the accumulator, and the inner loop consequently
		 * is run (hash_count[i]-HASH_LIMIT) times, removing
		 * one element from the list each time.  Since acc
		 * balances out to 0 at the final run, the inner loop
		 * body can't be left with entry==NULL.  So we indeed
		 * encounter entry==NULL in the outer loop only.
		 */
		do {
			acc += hash_count[i] - HASH_LIMIT;
			if (acc > 0) {
				struct unpacked_index_entry *keep = entry;
				do {
					entry = entry->next;
					acc -= HASH_LIMIT;
				} while (acc > 0);
				keep->next = entry->next;
			}
			entry = entry->next;
		} while (entry);
	}
	free(hash_count);

	/*
	 * Now create the packed index in array form
	 * rather than linked lists.
	 */
	memsize = sizeof(*index)
		+ sizeof(*packed_hash) * (hsize+1)
		+ sizeof(*packed_entry) * entries;
	mem = malloc(memsize);
	if (!mem) {
		free(hash);
		return NULL;
	}

	index = mem;
	index->memsize = memsize;
	index->src_buf = buf;
	index->src_size = bufsize;
	index->hash_mask = hmask;

	mem = index->hash;
	packed_hash = mem;
	mem = packed_hash + (hsize+1);
	packed_entry = mem;

	for (i = 0; i < hsize; i++) {
		/*
		 * Coalesce all entries belonging to one linked list
		 * into consecutive array entries.
		 */
		packed_hash[i] = packed_entry;
		for (entry = hash[i]; entry; entry = entry->next)
			*packed_entry++ = entry->entry;
	}

	/* Sentinel value to indicate the length of the last hash bucket */
	packed_hash[hsize] = packed_entry;

	assert(packed_entry - (struct index_entry *)mem == entries);
	free(hash);

	return index;
}