		else

			flags |= FILE_FLAG_SEQUENTIAL_SCAN;

		t->entry_fh = CreateFileW(tree_current_access_path(t),

		    GENERIC_READ, 0, NULL, OPEN_EXISTING, flags, NULL);

		if (t->entry_fh == INVALID_HANDLE_VALUE) {

			archive_set_error(&a->archive, errno,

			    "Couldn't open %ls", tree_current_path(a->tree));

