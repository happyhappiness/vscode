{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "File is beyond end-of-media: %s",
		    archive_entry_pathname(entry));
		iso9660->entry_bytes_remaining = 0;
		return (ARCHIVE_WARN);
	}