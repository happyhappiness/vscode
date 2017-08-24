{
		r = xmlTextWriterStartElement(writer, BAD_CAST("name"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterWriteAttribute(writer,
		    BAD_CAST("enctype"), BAD_CAST("base64"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterWriteBase64(writer, file->basename.s,
		    0, archive_strlen(&(file->basename)));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteBase64() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}