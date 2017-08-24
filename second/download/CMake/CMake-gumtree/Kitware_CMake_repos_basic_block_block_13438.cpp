{
		enum XML_Status xr;
		const void *d;
		size_t outbytes;
		size_t used;
		int r;

		d = NULL;
		r = rd_contents(a, &d, &outbytes, &used, xar->toc_remaining);
		if (r != ARCHIVE_OK)
			return (r);
		xar->toc_remaining -= used;
		xar->offset += used;
		xar->toc_total += outbytes;
		PRINT_TOC(d, outbytes);

		xr = XML_Parse(parser, d, outbytes, xar->toc_remaining == 0);
		__archive_read_consume(a, used);
		if (xr == XML_STATUS_ERROR) {
			XML_ParserFree(parser);
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "XML Parsing failed");
			return (ARCHIVE_FATAL);
		}
	}