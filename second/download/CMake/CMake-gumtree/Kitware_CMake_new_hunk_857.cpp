		uudecode->in_cnt = 0;
	}
	for (;used < avail_in; d += llen, used += llen) {
		int64_t l, body;

		b = d;
		len = get_line(b, avail_in - used, &nl);
		if (len < 0) {
			/* Non-ascii character is found. */
			if (uudecode->state == ST_FIND_HEAD &&
			    (uudecode->total > 0 || total > 0)) {
				uudecode->state = ST_IGNORE;
				used = avail_in;
				goto finish;
			}
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Insufficient compressed data");
