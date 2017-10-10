		append_basename(replacement, path[1], path[0]);
		path[1] = replacement->buf;
	}
}

void diff_no_index(struct rev_info *revs,
		   int argc, const char **argv)
{
	int i, prefixlen;
	const char *paths[2];
	struct strbuf replacement = STRBUF_INIT;
	const char *prefix = revs->prefix;

	diff_setup(&revs->diffopt);
	for (i = 1; i < argc - 2; ) {
		int j;
		if (!strcmp(argv[i], "--no-index"))
			i++;
		else if (!strcmp(argv[i], "--"))
			i++;
		else {
			j = diff_opt_parse(&revs->diffopt, argv + i, argc - i,
					   revs->prefix);
			if (j <= 0)
				die("invalid diff option/value: %s", argv[i]);
			i += j;
		}
	}

