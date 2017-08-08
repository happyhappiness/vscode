{
	struct warc_s *w = a->format_data;
	struct archive_string hdr;
#define MAX_HDR_SIZE 512

	/* check whether warcinfo record needs outputting */
	if (!w->omit_warcinfo) {
		ssize_t r;
		warc_essential_hdr_t wi = {
			WT_INFO,
			/*uri*/NULL,
			/*urn*/NULL,
			/*rtm*/0,
			/*mtm*/0,
			/*cty*/"application/warc-fields",
			/*len*/sizeof(warcinfo) - 1U,
		};
		wi.rtime = w->now;
		wi.mtime = w->now;

		archive_string_init(&hdr);
		r = _popul_ehdr(&hdr, MAX_HDR_SIZE, wi);
		if (r >= 0) {
			/* jackpot! */
			/* now also use HDR buffer for the actual warcinfo */
			archive_strncat(&hdr, warcinfo, sizeof(warcinfo) -1);

			/* append end-of-record indicator */
			archive_strncat(&hdr, "\r\n\r\n", 4);

			/* write to output stream */
			__archive_write_output(a, hdr.s, archive_strlen(&hdr));
		}
		/* indicate we're done with file header writing */
		w->omit_warcinfo = 1U;
		archive_string_free(&hdr);
	}

	if (archive_entry_pathname(entry) == NULL) {
		archive_set_error(&a->archive, EINVAL,
		    "Invalid filename");
		return (ARCHIVE_WARN);
	}

	w->typ = archive_entry_filetype(entry);
	w->populz = 0U;
	if (w->typ == AE_IFREG) {
		warc_essential_hdr_t rh = {
			WT_RSRC,
			/*uri*/NULL,
			/*urn*/NULL,
			/*rtm*/0,
			/*mtm*/0,
			/*cty*/NULL,
			/*len*/0,
		};
		ssize_t r;
		rh.tgturi = archive_entry_pathname(entry);
		rh.rtime = w->now;
		rh.mtime = archive_entry_mtime(entry);
		rh.cntlen = (size_t)archive_entry_size(entry);

		archive_string_init(&hdr);
		r = _popul_ehdr(&hdr, MAX_HDR_SIZE, rh);
		if (r < 0) {
			/* don't bother */
			archive_set_error(
				&a->archive,
				ARCHIVE_ERRNO_FILE_FORMAT,
				"cannot archive file");
			return (ARCHIVE_WARN);
		}
		/* otherwise append to output stream */
		__archive_write_output(a, hdr.s, r);
		/* and let subsequent calls to _data() know about the size */
		w->populz = rh.cntlen;
		archive_string_free(&hdr);
		return (ARCHIVE_OK);
	}
	/* just resort to erroring as per Tim's advice */
	archive_set_error(
		&a->archive,
		ARCHIVE_ERRNO_FILE_FORMAT,
		"WARC can only process regular files");
	return (ARCHIVE_FAILED);
}