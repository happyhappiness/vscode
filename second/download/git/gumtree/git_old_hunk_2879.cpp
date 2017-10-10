		}
	} else if (!strcmp(argv[0], "diff")) {
		if (setup_rerere(&merge_rr, flags | RERERE_READONLY) < 0)
			return 0;
		for (i = 0; i < merge_rr.nr; i++) {
			const char *path = merge_rr.items[i].string;
			const char *name = (const char *)merge_rr.items[i].util;
			if (diff_two(rerere_path(name, "preimage"), path, path, path))
				die("unable to generate diff for %s", name);
		}
	} else
		usage_with_options(rerere_usage, options);

	string_list_clear(&merge_rr, 1);
	return 0;
