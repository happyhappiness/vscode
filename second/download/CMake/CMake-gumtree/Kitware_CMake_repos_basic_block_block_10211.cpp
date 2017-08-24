{
		p = __archive_read_filter_ahead(filter, len + 2, &avail);
		if (p == NULL)
			return (0);
		len += ((int)p[len + 1] << 8) | (int)p[len];
		len += 2;
	}