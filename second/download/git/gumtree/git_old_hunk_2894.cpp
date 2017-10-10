		cmdmode = 'l';

	if ((annotate || msg.given || msgfile || force) && (cmdmode != 0))
		usage_with_options(git_tag_usage, options);

	finalize_colopts(&colopts, -1);
	if (cmdmode == 'l' && lines != -1) {
		if (explicitly_enable_column(colopts))
			die(_("--column and -n are incompatible"));
		colopts = 0;
	}
	if (cmdmode == 'l') {
		int ret;
		if (column_active(colopts)) {
			struct column_options copts;
			memset(&copts, 0, sizeof(copts));
			copts.padding = 2;
			run_column_filter(colopts, &copts);
		}
		if (lines != -1 && tag_sort)
			die(_("--sort and -n are incompatible"));
		ret = list_tags(argv, lines == -1 ? 0 : lines, with_commit, tag_sort);
		if (column_active(colopts))
			stop_column_filter();
		return ret;
	}
	if (lines != -1)
		die(_("-n option is only allowed with -l."));
	if (with_commit)
		die(_("--contains option is only allowed with -l."));
	if (points_at.nr)
		die(_("--points-at option is only allowed with -l."));
	if (cmdmode == 'd')
		return for_each_tag_name(argv, delete_tag);
	if (cmdmode == 'v')
		return for_each_tag_name(argv, verify_tag);

	if (msg.given || msgfile) {
