{
	struct archive_entry_linkresolver *res;

	/* Check for positive power-of-two */
	if (links_cache_initial_size == 0 ||
	    (links_cache_initial_size & (links_cache_initial_size - 1)) != 0)
		return (NULL);

	res = calloc(1, sizeof(struct archive_entry_linkresolver));
	if (res == NULL)
		return (NULL);
	res->number_buckets = links_cache_initial_size;
	res->buckets = calloc(res->number_buckets, sizeof(res->buckets[0]));
	if (res->buckets == NULL) {
		free(res);
		return (NULL);
	}
	return (res);
}