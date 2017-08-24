{
		const char *name;
		const void *value;
		size_t size;

		archive_entry_xattr_next(file->entry,
		    &name, &value, &size);
		r = xmlTextWriterStartElement(writer, BAD_CAST("ea"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterWriteFormatAttribute(writer,
		    BAD_CAST("id"), "%d", heap->id);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlwrite_heap(a, writer, heap);
		if (r < 0)
			return (ARCHIVE_FATAL);
		r = xmlwrite_string(a, writer, "name", name);
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