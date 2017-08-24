(xs) {
		size_t size = xs;
		if (size > wb_remaining(a))
			size = wb_remaining(a);
		memcpy(wb_buffptr(a), xp, size);
		if (wb_consume(a, size) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		xs -= size;
		xp += size;
	}