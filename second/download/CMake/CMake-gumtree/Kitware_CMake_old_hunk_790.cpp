		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Unexpected codec ID: %lX", zip->codec);

		return (ARCHIVE_FAILED);

	default:

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Unknown codec ID: %lX", zip->codec);

