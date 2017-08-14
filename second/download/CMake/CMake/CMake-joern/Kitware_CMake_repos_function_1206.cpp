static int
setup_sparse(struct archive_read_disk *a, struct archive_entry *entry)
{
	struct tree *t = a->tree;
	int64_t length, offset;
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
	for (i = 0; i < t->sparse_count; i++) {
		archive_entry_sparse_next(entry, &offset, &length);
		t->sparse_list[i].offset = offset;
		t->sparse_list[i].length = length;
	}
	if (i == 0) {
		t->sparse_list[i].offset = 0;
		t->sparse_list[i].length = archive_entry_size(entry);
	} else {
		t->sparse_list[i].offset = archive_entry_size(entry);
		t->sparse_list[i].length = 0;
	}
	t->current_sparse = t->sparse_list;

	return (ARCHIVE_OK);
}