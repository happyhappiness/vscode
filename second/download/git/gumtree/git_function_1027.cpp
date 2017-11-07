static void prepare_pack(int window, int depth)
{
	struct object_entry **delta_list;
	uint32_t i, nr_deltas;
	unsigned n;

	get_object_details();

	/*
	 * If we're locally repacking then we need to be doubly careful
	 * from now on in order to make sure no stealth corruption gets
	 * propagated to the new pack.  Clients receiving streamed packs
	 * should validate everything they get anyway so no need to incur
	 * the additional cost here in that case.
	 */
	if (!pack_to_stdout)
		do_check_packed_object_crc = 1;

	if (!to_pack.nr_objects || !window || !depth)
		return;

	ALLOC_ARRAY(delta_list, to_pack.nr_objects);
	nr_deltas = n = 0;

	for (i = 0; i < to_pack.nr_objects; i++) {
		struct object_entry *entry = to_pack.objects + i;

		if (entry->delta)
			/* This happens if we decided to reuse existing
			 * delta from a pack.  "reuse_delta &&" is implied.
			 */
			continue;

		if (entry->size < 50)
			continue;

		if (entry->no_try_delta)
			continue;

		if (!entry->preferred_base) {
			nr_deltas++;
			if (entry->type < 0)
				die("unable to get type of object %s",
				    sha1_to_hex(entry->idx.sha1));
		} else {
			if (entry->type < 0) {
				/*
				 * This object is not found, but we
				 * don't have to include it anyway.
				 */
				continue;
			}
		}

		delta_list[n++] = entry;
	}

	if (nr_deltas && n > 1) {
		unsigned nr_done = 0;
		if (progress)
			progress_state = start_progress(_("Compressing objects"),
							nr_deltas);
		QSORT(delta_list, n, type_size_sort);
		ll_find_deltas(delta_list, n, window+1, depth, &nr_done);
		stop_progress(&progress_state);
		if (nr_done != nr_deltas)
			die("inconsistency with delta count");
	}
	free(delta_list);
}