{
		h = __archive_read_ahead(a, newc_header_size, &bytes);
		if (h == NULL)
			return (ARCHIVE_FATAL);
		p = h;
		q = p + bytes;

		/* Try the typical case first, then go into the slow search.*/
		if (memcmp("07070", p, 5) == 0
		    && (p[5] == '1' || p[5] == '2')
		    && is_hex(p, newc_header_size))
			return (ARCHIVE_OK);

		/*
		 * Scan ahead until we find something that looks
		 * like a newc header.
		 */
		while (p + newc_header_size <= q) {
			switch (p[5]) {
			case '1':
			case '2':
				if (memcmp("07070", p, 5) == 0
				    && is_hex(p, newc_header_size)) {
					skip = p - (const char *)h;
					__archive_read_consume(a, skip);
					skipped += skip;
					if (skipped > 0) {
						archive_set_error(&a->archive,
						    0,
						    "Skipped %d bytes before "
						    "finding valid header",
						    (int)skipped);
						return (ARCHIVE_WARN);
					}
					return (ARCHIVE_OK);
				}
				p += 2;
				break;
			case '0':
				p++;
				break;
			default:
				p += 6;
				break;
			}
		}
		skip = p - (const char *)h;
		__archive_read_consume(a, skip);
		skipped += skip;
	}