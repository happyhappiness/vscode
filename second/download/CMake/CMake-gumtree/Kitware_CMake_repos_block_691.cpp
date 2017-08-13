{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "%s: Directories too deep.",
		    archive_entry_pathname(
			iso9660->directories_too_deep->file->entry));
		return (ARCHIVE_WARN);
	}