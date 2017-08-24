{
		/*
		 * Record TOC checksum
		 */
		r = xmlTextWriterStartElement(writer, BAD_CAST("checksum"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			goto exit_toc;
		}
		r = xmlTextWriterWriteAttribute(writer, BAD_CAST("style"),
		    BAD_CAST_CONST(getalgname(xar->opt_toc_sumalg)));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			goto exit_toc;
		}

		/*
		 * Record the offset of the value of checksum of TOC
		 */
		r = xmlwrite_string(a, writer, "offset", "0");
		if (r < 0)
			goto exit_toc;

		/*
		 * Record the size of the value of checksum of TOC
		 */
		r = xmlwrite_fstring(a, writer, "size", "%d", algsize);
		if (r < 0)
			goto exit_toc;

		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			goto exit_toc;
		}
	}