{
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterSetIndent() failed: %d", r);
		goto exit_toc;
	}