do {
			++len;
			if (avail < len)
				p = __archive_read_filter_ahead(filter,
				    len, &avail);
			if (p == NULL)
				return (0);
		} while (p[len - 1] != 0);