(file->ce_offset + file->ce_size > step) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Malformed CE information");
				return (ARCHIVE_FATAL);
			}