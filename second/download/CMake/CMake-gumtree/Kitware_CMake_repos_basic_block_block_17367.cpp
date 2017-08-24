{
		r = xmlTextWriterWriteAttribute(writer,
		    BAD_CAST_CONST(attrkey), BAD_CAST_CONST(attrvalue));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}