{
	struct xar *xar;
	enum la_zaction run;
	size_t size, rsize;
	int r;

	xar = (struct xar *)a->format_data;

	if (s > xar->bytes_remaining)
		s = (size_t)xar->bytes_remaining;
	if (s == 0 || xar->cur_file == NULL)
		return (0);
	if (xar->cur_file->data.compression == NONE) {
		checksum_update(&(xar->e_sumwrk), buff, s);
		checksum_update(&(xar->a_sumwrk), buff, s);
		size = rsize = s;
	} else {
		xar->stream.next_in = (const unsigned char *)buff;
		xar->stream.avail_in = s;
		if (xar->bytes_remaining > s)
			run = ARCHIVE_Z_RUN;
		else
			run = ARCHIVE_Z_FINISH;
		/* Compress file data. */
		r = compression_code(&(a->archive), &(xar->stream), run);
		if (r != ARCHIVE_OK && r != ARCHIVE_EOF)
			return (ARCHIVE_FATAL);
		rsize = s - xar->stream.avail_in;
		checksum_update(&(xar->e_sumwrk), buff, rsize);
		size = sizeof(xar->wbuff) - xar->stream.avail_out;
		checksum_update(&(xar->a_sumwrk), xar->wbuff, size);
	}
#if !defined(_WIN32) || defined(__CYGWIN__)
	if (xar->bytes_remaining ==
	    (uint64_t)archive_entry_size(xar->cur_file->entry)) {
		/*
		 * Get the path of a shell script if so.
		 */
		const unsigned char *b = (const unsigned char *)buff;

		archive_string_empty(&(xar->cur_file->script));
		if (rsize > 2 && b[0] == '#' && b[1] == '!') {
			size_t i, end, off;

			off = 2;
			if (b[off] == ' ')
				off++;
#ifdef PATH_MAX
			if ((rsize - off) > PATH_MAX)
				end = off + PATH_MAX;
			else
#endif
				end = rsize;
			/* Find the end of a script path. */
			for (i = off; i < end && b[i] != '\0' &&
			    b[i] != '\n' && b[i] != '\r' &&
			    b[i] != ' ' && b[i] != '\t'; i++)
				;
			archive_strncpy(&(xar->cur_file->script), b + off,
			    i - off);
		}
	}
#endif

	if (xar->cur_file->data.compression == NONE) {
		if (write_to_temp(a, buff, size) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	} else {
		if (write_to_temp(a, xar->wbuff, size) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}
	xar->bytes_remaining -= rsize;
	xar->cur_file->data.length += size;

	return (rsize);
}