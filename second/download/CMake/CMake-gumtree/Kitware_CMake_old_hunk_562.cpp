			rd_r = ARCHIVE_WARN;
		}
	} else {
		archive_string_empty(&iso9660->pathname);
		archive_entry_set_pathname(entry,
		    build_pathname(&iso9660->pathname, file));
	}

	iso9660->entry_bytes_remaining = file->size;
