archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (type=0%lo)",
			    (unsigned long)
			    archive_entry_filetype(entry_original))