	argc = parse_options(argc, argv, prefix, builtin_repack_options,
				git_repack_usage, 0);

	if (delete_redundant && repository_format_precious_objects)
		die(_("cannot delete packs in a precious-objects repo"));

	if (keep_unreachable &&
	    (unpack_unreachable || (pack_everything & LOOSEN_UNREACHABLE)))
		die(_("--keep-unreachable and -A are incompatible"));

	if (pack_kept_objects < 0)
		pack_kept_objects = write_bitmaps;

	packdir = mkpathdup("%s/pack", get_object_directory());
	packtmp = mkpathdup("%s/.tmp-%d-pack", packdir, (int)getpid());

