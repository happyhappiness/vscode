{
		/* PE file */
		offset = 0;
		window = 4096;
		while (offset < (1024 * 20)) {
			buff = __archive_read_ahead(a, offset + window,
			    &bytes_avail);
			if (buff == NULL) {
				/* Remaining bytes are less than window. */
				window >>= 1;
				if (window < (H_SIZE + 3))
					return (0);
				continue;
			}
			p = (const char *)buff + offset;
			while (p + H_SIZE < (const char *)buff + bytes_avail) {
				if ((next = lha_check_header_format(p)) == 0)
					return (30);
				p += next;
			}
			offset = p - (const char *)buff;
		}
	}