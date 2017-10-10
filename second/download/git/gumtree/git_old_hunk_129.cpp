		if (column_active(colopts)) {
			struct column_options copts;
			memset(&copts, 0, sizeof(copts));
			copts.padding = 2;
			run_column_filter(colopts, &copts);
		}
		if (lines != -1 && sort)
			die(_("--sort and -n are incompatible"));
		ret = list_tags(argv, lines == -1 ? 0 : lines, with_commit, sort);
		if (column_active(colopts))
			stop_column_filter();
		return ret;
	}
	if (lines != -1)
		die(_("-n option is only allowed with -l."));
