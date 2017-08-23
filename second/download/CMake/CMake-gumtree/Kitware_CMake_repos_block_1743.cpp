{
					archive_set_error(&a->archive,
					    ENOMEM,
					    "Can't allocate memory");
					archive_entry_free(entry_main);
					archive_string_free(&entry_name);
					return (ARCHIVE_FATAL);
				}