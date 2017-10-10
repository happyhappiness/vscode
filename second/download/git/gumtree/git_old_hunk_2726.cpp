
	git_config(repack_config, NULL);

	argc = parse_options(argc, argv, prefix, builtin_repack_options,
				git_repack_usage, 0);

	if (pack_kept_objects < 0)
		pack_kept_objects = write_bitmaps;

	packdir = mkpathdup("%s/pack", get_object_directory());
	packtmp = mkpathdup("%s/.tmp-%d-pack", packdir, (int)getpid());

