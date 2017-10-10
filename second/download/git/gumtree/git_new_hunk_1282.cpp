		opt.output = append_path;
		string_list_append(&path_list, show_in_pager);
	}

	if (!opt.pattern_list)
		die(_("no pattern given."));

	/*
	 * We have to find "--" in a separate pass, because its presence
	 * influences how we will parse arguments that come before it.
	 */
	for (i = 0; i < argc; i++) {
