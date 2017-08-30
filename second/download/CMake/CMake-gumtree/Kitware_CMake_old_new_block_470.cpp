((en == EISDIR || en == EEXIST)
	    && (a->flags & ARCHIVE_EXTRACT_NO_OVERWRITE)) {
		/* If we're not overwriting, we're done. */
		archive_entry_unset_size(a->entry);
		return (ARCHIVE_OK);
	}