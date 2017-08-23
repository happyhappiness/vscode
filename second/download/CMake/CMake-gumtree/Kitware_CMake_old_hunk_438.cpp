		}

		if (a->read_data_offset < a->read_data_output_offset) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Encountered out-of-order sparse blocks");
			return (ARCHIVE_RETRY);
		}
