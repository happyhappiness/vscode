	unsigned foreign_nr = 1;	/* zero is a "good" value, assume bad */

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(index_pack_usage);

	check_replace_refs = 0;
	fsck_options.walk = mark_link;

	reset_pack_idx_option(&opts);
	git_config(git_index_pack_config, &opts);
	if (prefix && chdir(prefix))
		die(_("Cannot come back to cwd"));

