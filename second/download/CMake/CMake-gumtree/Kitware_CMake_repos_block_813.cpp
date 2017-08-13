{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed PPMd parameter");
			return (ARCHIVE_FAILED);
		}