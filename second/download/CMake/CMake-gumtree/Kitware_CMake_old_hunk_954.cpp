			    iso9660->previous_pathname.s);

		archive_entry_unset_size(entry);

		iso9660->entry_bytes_remaining = 0;

		iso9660->entry_sparse_offset = 0;

		return (rd_r);

	}



	/* Except for the hardlink case above, if the offset of the

	 * next entry is before our current position, we can't seek

	 * backwards to extract it, so issue a warning.  Note that

	 * this can only happen if this entry was added to the heap

	 * after we passed this offset, that is, only if the directory

	 * mentioning this entry is later than the body of the entry.

	 * Such layouts are very unusual; most ISO9660 writers lay out

	 * and record all directory information first, then store

	 * all file bodies. */

	/* TODO: Someday, libarchive's I/O core will support optional

	 * seeking.  When that day comes, this code should attempt to

	 * seek and only return the error if the seek fails.  That

	 * will give us support for whacky ISO images that require

	 * seeking while retaining the ability to read almost all ISO

	 * images in a streaming fashion. */

	if ((file->mode & AE_IFMT) != AE_IFDIR &&

	    file->offset < iso9660->current_position) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Ignoring out-of-order file @%jx (%s) %jd < %jd",

		    (intmax_t)file->number,

		    iso9660->pathname.s,

		    (intmax_t)file->offset,

		    (intmax_t)iso9660->current_position);

		iso9660->entry_bytes_remaining = 0;

		iso9660->entry_sparse_offset = 0;

		return (ARCHIVE_WARN);

	}



	/* Initialize zisofs variables. */

