	 * that we change to some uid other than the current one, then
	 * log a warning. */

	/* TODO: Perhaps take a list of gids, and make them into the
	 * supplementary groups. */

	if (use_chroot || (module_dirlen = strlen(lp_path(i))) == 1) {
		module_dirlen = 0;
		set_filter_dir("/", 1);
	} else
		set_filter_dir(lp_path(i), module_dirlen);

	p = lp_filter(i);
	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
		   XFLG_ABS_IF_SLASH);

	p = lp_include_from(i);
