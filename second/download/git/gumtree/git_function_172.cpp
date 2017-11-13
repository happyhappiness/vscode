static int fetch_dumb(int nr_heads, struct ref **to_fetch)
{
	struct walker *walker;
	char **targets = xmalloc(nr_heads * sizeof(char*));
	int ret, i;

	if (options.depth)
		die("dumb http transport does not support --depth");
	for (i = 0; i < nr_heads; i++)
		targets[i] = xstrdup(sha1_to_hex(to_fetch[i]->old_sha1));

	walker = get_http_walker(url.buf);
	walker->get_all = 1;
	walker->get_tree = 1;
	walker->get_history = 1;
	walker->get_verbosely = options.verbosity >= 3;
	walker->get_recover = 0;
	ret = walker_fetch(walker, nr_heads, targets, NULL, NULL);
	walker_free(walker);

	for (i = 0; i < nr_heads; i++)
		free(targets[i]);
	free(targets);

	return ret ? error("Fetch failed.") : 0;
}