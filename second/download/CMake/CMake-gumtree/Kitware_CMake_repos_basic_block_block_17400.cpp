{
		r = xmlTextWriterStartElement(writer, BAD_CAST("content"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}

		r = xmlwrite_string(a, writer,
		    "interpreter", file->script.s);
		if (r < 0)
			return (ARCHIVE_FATAL);

		r = xmlwrite_string(a, writer, "type", "script");
		if (r < 0)
			return (ARCHIVE_FATAL);

		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}