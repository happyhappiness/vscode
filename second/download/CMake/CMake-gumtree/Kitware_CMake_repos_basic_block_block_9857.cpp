{
		result = &grent; /* Old getgrgid_r ignores last arg. */
		r = getgrgid_r((gid_t)id, &grent,
			       cache->buff, cache->buff_size, &result);
		if (r == 0)
			break;
		if (r != ERANGE)
			break;
		/* ERANGE means our buffer was too small, but POSIX
		 * doesn't tell us how big the buffer should be, so
		 * we just double it and try again. */
		nbuff_size = cache->buff_size * 2;
		nbuff = realloc(cache->buff, nbuff_size);
		if (nbuff == NULL)
			break;
		cache->buff = nbuff;
		cache->buff_size = nbuff_size;
	}