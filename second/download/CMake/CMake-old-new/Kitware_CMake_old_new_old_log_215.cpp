archive_set_error(&a->archive,
									ARCHIVE_ERRNO_MISC,
									"mtree specification has different type for %s",
									archive_entry_pathname(entry));