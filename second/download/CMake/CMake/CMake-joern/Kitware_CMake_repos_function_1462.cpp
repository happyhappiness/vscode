static int
setup_sparse(struct archive_read_disk *a, struct archive_entry *entry)
{
	struct tree *t = a->tree;
	int64_t aligned, length, offset;
	int i;

	t->sparse_count = archive_entry_sparse_reset(entry);
	if (t->sparse_count+1 > t->sparse_list_size) {
		free(t->sparse_list);
		t->sparse_list_size = t->sparse_count + 1;
		t->sparse_list = malloc(sizeof(t->sparse_list[0]) *
		    t->sparse_list_size);
		if (t->sparse_list == NULL) {
			t->sparse_list_size = 0;
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate data");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}
	}
	/*
	 * Get sparse list and make sure those offsets and lengths are
	 * aligned by a sector size.
	 */
	for (i = 0; i < t->sparse_count; i++) {
		archive_entry_sparse_next(entry, &offset, &length);
		aligned = align_num_per_sector(t, offset);
		if (aligned != offset) {
			aligned -= t->current_filesystem->bytesPerSector;
			length += offset - aligned;
		}
		t->sparse_list[i].offset = aligned;
		aligned = align_num_per_sector(t, length);
		t->sparse_list[i].length = aligned;
	}

	aligned = align_num_per_sector(t, archive_entry_size(entry));
	if (i == 0) {
		t->sparse_list[i].offset = 0;
		t->sparse_list[i].length = aligned;
	} else {
		int j, last = i;

		t->sparse_list[i].offset = aligned;
		t->sparse_list[i].length = 0;
		for (i = 0; i < last; i++) {
			if ((t->sparse_list[i].offset +
			       t->sparse_list[i].length) <= 
					t->sparse_list[i+1].offset)
				continue;
			/*
			 * Now sparse_list[i+1] is overlapped by sparse_list[i].
			 * Merge those two.
			 */
			length = t->sparse_list[i+1].offset -
					t->sparse_list[i].offset;
			t->sparse_list[i+1].offset = t->sparse_list[i].offset;
			t->sparse_list[i+1].length += length;
			/* Remove sparse_list[i]. */
			for (j = i; j < last; j++) {
				t->sparse_list[j].offset =
				    t->sparse_list[j+1].offset;
				t->sparse_list[j].length =
				    t->sparse_list[j+1].length;
			}
			last--;
		}
	}
	t->current_sparse = t->sparse_list;

	return (ARCHIVE_OK);
}