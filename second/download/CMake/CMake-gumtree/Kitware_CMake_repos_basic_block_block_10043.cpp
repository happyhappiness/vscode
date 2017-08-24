(extract->ad == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Can't extract");
			return (ARCHIVE_FATAL);
		}