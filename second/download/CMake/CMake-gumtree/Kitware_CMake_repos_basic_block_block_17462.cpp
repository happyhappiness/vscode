(np != np->parent) {
			r = xmlTextWriterEndElement(writer);
			if (r < 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "xmlTextWriterEndElement() "
				    "failed: %d", r);
				goto exit_toc;
			}
			if (np->chnext == NULL) {
				/* Return to the parent directory. */
				np = np->parent;
			} else {
				np = np->chnext;
				r = xmlTextWriterStartElement(writer,
				    BAD_CAST("file"));
				if (r < 0) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "xmlTextWriterStartElement() "
					    "failed: %d", r);
					goto exit_toc;
				}
				r = xmlTextWriterWriteFormatAttribute(
				    writer, BAD_CAST("id"), "%d", np->id);
				if (r < 0) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "xmlTextWriterWriteAttribute() "
					    "failed: %d", r);
					goto exit_toc;
				}
				break;
			}
		}