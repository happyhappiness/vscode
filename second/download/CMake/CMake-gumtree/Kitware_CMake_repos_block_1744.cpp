{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "archive_write_pax_header: "
			    "'x' header failed?!  This can't happen.\n");
			return (ARCHIVE_FATAL);
		}