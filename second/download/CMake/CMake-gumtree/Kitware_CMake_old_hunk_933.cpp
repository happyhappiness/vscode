		uudecode->in_cnt = 0;

	}

	for (;used < avail_in; d += llen, used += llen) {

		int l, body;



		b = d;

		len = get_line(b, avail_in - used, &nl);

		if (len < 0) {

			/* Non-ascii character is found. */

			archive_set_error(&self->archive->archive,

			    ARCHIVE_ERRNO_MISC,

			    "Insufficient compressed data");

