struct walker *get_http_walker(const char *url)
{
	char *s;
	struct walker_data *data = xmalloc(sizeof(struct walker_data));
	struct walker *walker = xmalloc(sizeof(struct walker));

	data->alt = xmalloc(sizeof(*data->alt));
	data->alt->base = xstrdup(url);
	for (s = data->alt->base + strlen(data->alt->base) - 1; *s == '/'; --s)
		*s = 0;

	data->alt->got_indices = 0;
	data->alt->packs = NULL;
	data->alt->next = NULL;
	data->got_alternates = -1;

	walker->corrupt_object_found = 0;
	walker->fetch = fetch;
	walker->fetch_ref = fetch_ref;
	walker->prefetch = prefetch;
	walker->cleanup = cleanup;
	walker->data = data;

#ifdef USE_CURL_MULTI
	add_fill_function(walker, (int (*)(void *)) fill_active_slot);
#endif

	return walker;
}