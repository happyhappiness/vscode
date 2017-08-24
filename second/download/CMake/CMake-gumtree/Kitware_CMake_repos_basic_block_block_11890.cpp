{
		h = __archive_read_ahead(a, window, &bytes);
		if (h == NULL) {
			/* Remaining bytes are less than window. */
			window >>= 1;
			if (window < (H_SIZE + 3))
				goto fatal;
			continue;
		}
		if (bytes < H_SIZE)
			goto fatal;
		p = h;
		q = p + bytes;

		/*
		 * Scan ahead until we find something that looks
		 * like the lha header.
		 */
		while (p + H_SIZE < q) {
			if ((next = lha_check_header_format(p)) == 0) {
				skip = p - (const char *)h;
				__archive_read_consume(a, skip);
				return (ARCHIVE_OK);
			}
			p += next;
		}
		skip = p - (const char *)h;
		__archive_read_consume(a, skip);
	}