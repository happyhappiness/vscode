			    iso9660->previous_pathname.s);

		archive_entry_unset_size(entry);

		iso9660->entry_bytes_remaining = 0;

		return (rd_r);

	}



	if ((file->mode & AE_IFMT) != AE_IFDIR &&

	    file->offset < iso9660->current_position) {

		int64_t r64;



		r64 = __archive_read_seek(a, file->offset, SEEK_SET);

		if (r64 != (int64_t)file->offset) {

			/* We can't seek backwards to extract it, so issue

			 * a warning.  Note that this can only happen if

			 * this entry was added to the heap after we passed

			 * this offset, that is, only if the directory

			 * mentioning this entry is later than the body of

			 * the entry. Such layouts are very unusual; most

			 * ISO9660 writers lay out and record all directory

			 * information first, then store all file bodies. */

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "Ignoring out-of-order file @%jx (%s) %jd < %jd",

			    (intmax_t)file->number,

			    iso9660->pathname.s,

			    (intmax_t)file->offset,

			    (intmax_t)iso9660->current_position);

			iso9660->entry_bytes_remaining = 0;

			return (ARCHIVE_WARN);

		}

		iso9660->current_position = (uint64_t)r64;

	}



	/* Initialize zisofs variables. */

