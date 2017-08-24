{
		p = __archive_read_ahead(a, min, avail);
		if (p != NULL)
			return (p);
		min--;
	}