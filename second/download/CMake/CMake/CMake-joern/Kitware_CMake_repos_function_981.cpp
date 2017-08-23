static int
make_toc(struct archive_write *a)
{
	struct xar *xar;
	struct file *np;
	xmlBufferPtr bp;
	xmlTextWriterPtr writer;
	int algsize;
	int r, ret;

	xar = (struct xar *)a->format_data;

	ret = ARCHIVE_FATAL;

	/*
	 * Initialize xml writer.
	 */
	writer = NULL;
	bp = xmlBufferCreate();
	if (bp == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "xmlBufferCreate() "
		    "couldn't create xml buffer");
		goto exit_toc;
	}
	writer = xmlNewTextWriterMemory(bp, 0);
	if (writer == NULL) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlNewTextWriterMemory() "
		    "couldn't create xml writer");
		goto exit_toc;
	}
	r = xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterStartDocument() failed: %d", r);
		goto exit_toc;
	}
	r = xmlTextWriterSetIndent(writer, 4);
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterSetIndent() failed: %d", r);
		goto exit_toc;
	}

	/*
	 * Start recording TOC
	 */
	r = xmlTextWriterStartElement(writer, BAD_CAST("xar"));
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterStartElement() failed: %d", r);
		goto exit_toc;
	}
	r = xmlTextWriterStartElement(writer, BAD_CAST("toc"));
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterStartDocument() failed: %d", r);
		goto exit_toc;
	}

	/*
	 * Record the creation time of the archive file.
	 */
	r = xmlwrite_time(a, writer, "creation-time", time(NULL), 0);
	if (r < 0)
		goto exit_toc;

	/*
	 * Record the checksum value of TOC
	 */
	algsize = getalgsize(xar->opt_toc_sumalg);
	if (algsize) {
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

	np = xar->root;
	do {
		if (np != np->parent) {
			r = make_file_entry(a, writer, np);
			if (r != ARCHIVE_OK)
				goto exit_toc;
		}

		if (np->dir && np->children.first != NULL) {
			/* Enter to sub directories. */
			np = np->children.first;
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
			continue;
		}
		while (np != np->parent) {
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
	} while (np != np->parent);

	r = xmlTextWriterEndDocument(writer);
	if (r < 0) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterEndDocument() failed: %d", r);
		goto exit_toc;
	}
#if DEBUG_PRINT_TOC
	fprintf(stderr, "\n---TOC-- %d bytes --\n%s\n",
	    strlen((const char *)bp->content), bp->content);
#endif

	/*
	 * Compress the TOC and calculate the sum of the TOC.
	 */
	xar->toc.temp_offset = xar->temp_offset;
	xar->toc.size = bp->use;
	checksum_init(&(xar->a_sumwrk), xar->opt_toc_sumalg);

	r = compression_init_encoder_gzip(&(a->archive),
	    &(xar->stream), 6, 1);
	if (r != ARCHIVE_OK)
		goto exit_toc;
	xar->stream.next_in = bp->content;
	xar->stream.avail_in = bp->use;
	xar->stream.total_in = 0;
	xar->stream.next_out = xar->wbuff;
	xar->stream.avail_out = sizeof(xar->wbuff);
	xar->stream.total_out = 0;
	for (;;) {
		size_t size;

		r = compression_code(&(a->archive),
		    &(xar->stream), ARCHIVE_Z_FINISH);
		if (r != ARCHIVE_OK && r != ARCHIVE_EOF)
			goto exit_toc;
		size = sizeof(xar->wbuff) - xar->stream.avail_out;
		checksum_update(&(xar->a_sumwrk), xar->wbuff, size);
		if (write_to_temp(a, xar->wbuff, size) != ARCHIVE_OK)
			goto exit_toc;
		if (r == ARCHIVE_EOF)
			break;
		xar->stream.next_out = xar->wbuff;
		xar->stream.avail_out = sizeof(xar->wbuff);
	}
	r = compression_end(&(a->archive), &(xar->stream));
	if (r != ARCHIVE_OK)
		goto exit_toc;
	xar->toc.length = xar->stream.total_out;
	xar->toc.compression = GZIP;
	checksum_final(&(xar->a_sumwrk), &(xar->toc.a_sum));

	ret = ARCHIVE_OK;
exit_toc:
	if (writer)
		xmlFreeTextWriter(writer);
	if (bp)
		xmlBufferFree(bp);

	return (ret);
}