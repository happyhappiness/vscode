			   that are longer than this, so a failure to get at

			   least 16 bytes really does indicate a truncated

			   file. */

			archive_set_error(&a->archive,

			    ARCHIVE_ERRNO_FILE_FORMAT,

			    "Truncated ZIP file data");

			return (ARCHIVE_FATAL);

		}

