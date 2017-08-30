			rd_r = ARCHIVE_WARN;
		}
	} else {
		const char *path = build_pathname(&iso9660->pathname, file, 0);
		if (path == NULL) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname is too long");
			return (ARCHIVE_FATAL);
		} else {
			archive_string_empty(&iso9660->pathname);
			archive_entry_set_pathname(entry, path);
		}
	}

	iso9660->entry_bytes_remaining = file->size;
