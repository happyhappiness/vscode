{
	int r;

	r = xmlTextWriterStartElement(writer, BAD_CAST_CONST(key));
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterStartElement() failed: %d", r);
		return (ARCHIVE_FATAL);
	}
	if (attrkey != NULL && attrvalue != NULL) {
		r = xmlTextWriterWriteAttribute(writer,
		    BAD_CAST_CONST(attrkey), BAD_CAST_CONST(attrvalue));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}
	if (value != NULL) {
		r = xmlTextWriterWriteString(writer, BAD_CAST_CONST(value));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteString() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}
	r = xmlTextWriterEndElement(writer);
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterEndElement() failed: %d", r);
		return (ARCHIVE_FATAL);
	}
	return (ARCHIVE_OK);
}