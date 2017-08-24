	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t = a->tree;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
	    "archive_read_disk_descend");

	if (t->visit_type != TREE_REGULAR || !t->descend) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Ignored the request descending the current object");
		return (ARCHIVE_WARN);
	}

	if (tree_current_is_physical_dir(t)) {
		tree_push(t, t->basename, t->current_filesystem_id,
