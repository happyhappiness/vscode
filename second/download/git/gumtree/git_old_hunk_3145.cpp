		opt.color = 0;
		opt.name_only = 1;
		opt.null_following_name = 1;
		opt.output_priv = &path_list;
		opt.output = append_path;
		string_list_append(&path_list, show_in_pager);
		use_threads = 0;
	}

	if (!opt.pattern_list)
		die(_("no pattern given."));
	if (!opt.fixed && opt.ignore_case)
		opt.regflags |= REG_ICASE;
