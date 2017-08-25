(archive_entry_filetype(entry) == AE_IFREG &&
	    archive_entry_size(entry) > 0) {
		t->entry_fh = CreateFileW(tree_current_access_path(t),
		    GENERIC_READ, 0, NULL, OPEN_EXISTING,
		    FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (t->entry_fh == INVALID_HANDLE_VALUE) {
			archive_set_error(&a->archive, errno,
			    "Couldn't open %ls", tree_current_path(a->tree));
			return (ARCHIVE_FAILED);
		}

		/* Find sparse data from the disk. */
		if (archive_entry_hardlink(entry) == NULL &&
		    (st->dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) != 0)
			r = setup_sparse_from_disk(a, entry, t->entry_fh);
	}