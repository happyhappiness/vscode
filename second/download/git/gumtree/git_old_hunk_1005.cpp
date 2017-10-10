			if (j <= 0)
				die("invalid diff option/value: %s", argv[i]);
			i += j;
		}
	}

	prefixlen = prefix ? strlen(prefix) : 0;
	for (i = 0; i < 2; i++) {
		const char *p = argv[argc - 2 + i];
		if (!strcmp(p, "-"))
			/*
			 * stdin should be spelled as "-"; if you have
			 * path that is "-", spell it as "./-".
			 */
			p = file_from_standard_input;
		else if (prefixlen)
			p = xstrdup(prefix_filename(prefix, prefixlen, p));
		paths[i] = p;
	}

	fixup_paths(paths, &replacement);

	revs->diffopt.skip_stat_unmatch = 1;
