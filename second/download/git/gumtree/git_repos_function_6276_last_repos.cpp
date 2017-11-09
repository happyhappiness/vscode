static void get_object_details(void)
{
	uint32_t i;
	struct object_entry **sorted_by_offset;

	sorted_by_offset = xcalloc(to_pack.nr_objects, sizeof(struct object_entry *));
	for (i = 0; i < to_pack.nr_objects; i++)
		sorted_by_offset[i] = to_pack.objects + i;
	QSORT(sorted_by_offset, to_pack.nr_objects, pack_offset_sort);

	for (i = 0; i < to_pack.nr_objects; i++) {
		struct object_entry *entry = sorted_by_offset[i];
		check_object(entry);
		if (big_file_threshold < entry->size)
			entry->no_try_delta = 1;
	}

	/*
	 * This must happen in a second pass, since we rely on the delta
	 * information for the whole list being completed.
	 */
	for (i = 0; i < to_pack.nr_objects; i++)
		break_delta_chains(&to_pack.objects[i]);

	free(sorted_by_offset);
}