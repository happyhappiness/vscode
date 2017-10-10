		pathspec->nr = 1;
		pathspec->_raw = raw;
		return;
	}

	n = 0;
	while (argv[n])
		n++;

	pathspec->nr = n;
	ALLOC_ARRAY(pathspec->items, n);
	item = pathspec->items;
	pathspec->_raw = argv;
	prefixlen = prefix ? strlen(prefix) : 0;
