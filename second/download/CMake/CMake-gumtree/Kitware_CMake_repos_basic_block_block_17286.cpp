{
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