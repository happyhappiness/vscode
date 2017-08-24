		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	t->descend = descend;

	archive_entry_copy_pathname_w(entry, tree_current_path(t));
	archive_entry_copy_sourcepath_w(entry, tree_current_access_path(t));
	tree_archive_entry_copy_bhfi(entry, t, st);

	/* Save the times to be restored. */
	t->restore_time.lastWriteTime = st->ftLastWriteTime;
	t->restore_time.lastAccessTime = st->ftLastAccessTime;
	t->restore_time.filetype = archive_entry_filetype(entry);

	/* Lookup uname/gname */
	name = archive_read_disk_uname(_a, archive_entry_uid(entry));
	if (name != NULL)
		archive_entry_copy_uname(entry, name);
	name = archive_read_disk_gname(_a, archive_entry_gid(entry));
	if (name != NULL)
		archive_entry_copy_gname(entry, name);

	r = ARCHIVE_OK;
	if (archive_entry_filetype(entry) == AE_IFREG &&
	    archive_entry_size(entry) > 0) {
		t->entry_fh = CreateFileW(tree_current_access_path(t),
		    GENERIC_READ, 0, NULL, OPEN_EXISTING,
		    FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (t->entry_fh == INVALID_HANDLE_VALUE) {
			archive_set_error(&a->archive, errno,
			    "Couldn't open %ls", tree_current_path(a->tree));
