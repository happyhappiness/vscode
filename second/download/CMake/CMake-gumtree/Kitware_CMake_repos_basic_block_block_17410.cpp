{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}