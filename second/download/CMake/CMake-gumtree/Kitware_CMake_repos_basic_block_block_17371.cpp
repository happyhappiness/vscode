{
		r = xmlTextWriterWriteString(writer, BAD_CAST_CONST(value));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteString() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}