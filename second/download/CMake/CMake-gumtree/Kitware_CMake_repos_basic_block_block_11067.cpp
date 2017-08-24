(p[0] == 'M' && p[1] == 'Z') {
		offset = 0;
		window = 4096;
		while (offset < (1024 * 128)) {
			const char *h = __archive_read_ahead(a, offset + window,
			    &bytes_avail);
			if (h == NULL) {
				/* Remaining bytes are less than window. */
				window >>= 1;
				if (window < 128)
					return (0);
				continue;
			}
			p = h + offset;
			while (p + 8 < h + bytes_avail) {
				int next;
				if ((next = find_cab_magic(p)) == 0)
					return (64);
				p += next;
			}
			offset = p - h;
		}
	}