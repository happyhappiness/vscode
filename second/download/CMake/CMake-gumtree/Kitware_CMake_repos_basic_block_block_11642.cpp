(iso9660->utf16be_path == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory");
				return (ARCHIVE_FATAL);
			}