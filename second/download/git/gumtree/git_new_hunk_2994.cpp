	char **targets = xmalloc(nr_heads * sizeof(char*));
	int ret, i;

	if (options.depth)
		die("dumb http transport does not support --depth");
	for (i = 0; i < nr_heads; i++)
		targets[i] = xstrdup(oid_to_hex(&to_fetch[i]->old_oid));

	walker = get_http_walker(url.buf);
	walker->get_all = 1;
	walker->get_tree = 1;
	walker->get_history = 1;
	walker->get_verbosely = options.verbosity >= 3;
