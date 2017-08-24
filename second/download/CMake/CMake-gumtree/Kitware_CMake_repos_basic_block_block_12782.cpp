(a->archive.archive_format == ARCHIVE_FORMAT_TAR
		    || a->archive.archive_format == ARCHIVE_FORMAT_TAR_GNUTAR)
		{
			/* Old-style or GNU tar: we must ignore the size. */
			archive_entry_set_size(entry, 0);
			tar->entry_bytes_remaining = 0;
		}