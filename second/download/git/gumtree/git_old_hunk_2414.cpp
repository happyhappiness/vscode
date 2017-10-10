				merge_rr.items[i].util = NULL;
		}
	} else if (!strcmp(argv[0], "diff"))
		for (i = 0; i < merge_rr.nr; i++) {
			const char *path = merge_rr.items[i].string;
			const char *name = (const char *)merge_rr.items[i].util;
			diff_two(rerere_path(name, "preimage"), path, path, path);
		}
	else
		usage_with_options(rerere_usage, options);

	string_list_clear(&merge_rr, 1);
	return 0;
