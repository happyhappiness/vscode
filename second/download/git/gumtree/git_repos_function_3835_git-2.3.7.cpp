static struct entry *find_longest_common_sequence(struct hashmap *map)
{
	struct entry **sequence = xdl_malloc(map->nr * sizeof(struct entry *));
	int longest = 0, i;
	struct entry *entry;

	for (entry = map->first; entry; entry = entry->next) {
		if (!entry->line2 || entry->line2 == NON_UNIQUE)
			continue;
		i = binary_search(sequence, longest, entry);
		entry->previous = i < 0 ? NULL : sequence[i];
		sequence[++i] = entry;
		if (i == longest)
			longest++;
	}

	/* No common unique lines were found */
	if (!longest) {
		xdl_free(sequence);
		return NULL;
	}

	/* Iterate starting at the last element, adjusting the "next" members */
	entry = sequence[longest - 1];
	entry->next = NULL;
	while (entry->previous) {
		entry->previous->next = entry;
		entry = entry->previous;
	}
	xdl_free(sequence);
	return entry;
}