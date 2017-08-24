(xar->entry_remaining > 0)
		/* Move reading point to the beginning of current
		 * file contents. */
		r = move_reading_point(a, file->offset);
	else
		r = ARCHIVE_OK