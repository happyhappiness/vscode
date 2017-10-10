			struct column_options copts;
			memset(&copts, 0, sizeof(copts));
			copts.padding = 2;
			run_column_filter(colopts, &copts);
		}
		filter.name_patterns = argv;
		ret = list_tags(&filter, sorting, &format);
		if (column_active(colopts))
			stop_column_filter();
		return ret;
	}
	if (filter.lines != -1)
		die(_("-n option is only allowed in list mode"));
