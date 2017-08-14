static const char *
lookup_gname_helper(struct name_cache *cache, id_t id)
{
	struct group	grent, *result;
	char * nbuff;
	size_t nbuff_size;
	int r;

	if (cache->buff_size == 0) {
		cache->buff_size = 256;
		cache->buff = malloc(cache->buff_size);
	}
	if (cache->buff == NULL)
		return (NULL);
	for (;;) {
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
	if (r != 0) {
		archive_set_error(cache->archive, errno,
		    "Can't lookup group for id %d", (int)id);
		return (NULL);
	}
	if (result == NULL)
		return (NULL);

	return strdup(result->gr_name);
}