		en = create_filesystem_object(a);
	}

	if ((en == ENOENT) && (archive_entry_hardlink(a->entry) != NULL)) {
		archive_set_error(&a->archive, en,
		    "Hard-link target '%s' does not exist.",
		    archive_entry_hardlink(a->entry));
		return (ARCHIVE_FAILED);
	}

	if ((en == EISDIR || en == EEXIST)
	    && (a->flags & ARCHIVE_EXTRACT_NO_OVERWRITE)) {
		/* If we're not overwriting, we're done. */
