{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t = a->tree;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_read_disk_descend");

	if (t->visit_type != TREE_REGULAR || !t->descend)
		return (ARCHIVE_OK);

	if (tree_current_is_physical_dir(t)) {
		tree_push(t, t->basename, t->full_path.s,
		    t->current_filesystem_id,
		    bhfi_dev(&(t->lst)), bhfi_ino(&(t->lst)),
		    &t->restore_time);
		t->stack->flags |= isDir;
	} else if (tree_current_is_dir(t)) {
		tree_push(t, t->basename, t->full_path.s,
		    t->current_filesystem_id,
		    bhfi_dev(&(t->st)), bhfi_ino(&(t->st)),
		    &t->restore_time);
		t->stack->flags |= isDirLink;
	}
	t->descend = 0;
	return (ARCHIVE_OK);
}