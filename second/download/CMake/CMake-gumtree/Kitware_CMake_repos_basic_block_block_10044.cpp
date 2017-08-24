(extract->ad == NULL) {
		extract->ad = archive_write_disk_new();
		if (extract->ad == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Can't extract");
			return (ARCHIVE_FATAL);
		}
		archive_write_disk_set_standard_lookup(extract->ad);
	}