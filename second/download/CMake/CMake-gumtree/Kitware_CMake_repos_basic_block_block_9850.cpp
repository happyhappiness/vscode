{
		result = &pwent; /* Old getpwuid_r ignores last arg. */
		r = getpwuid_r((uid_t)id, &pwent,
			       cache->buff, cache->buff_size, &result);
		if (r == 0)
			break;
		if (r != ERANGE)
			break;
		/* ERANGE means our buffer was too small, but POSIX
		 * doesn't tell us how big the buffer should be, so
		 * we just double it and try again.  Because the buffer
		 * is kept around in the cache object, we shouldn't
		 * have to do this very often. */
		nbuff_size = cache->buff_size * 2;
		nbuff = realloc(cache->buff, nbuff_size);
		if (nbuff == NULL)
			break;
		cache->buff = nbuff;
		cache->buff_size = nbuff_size;
	}