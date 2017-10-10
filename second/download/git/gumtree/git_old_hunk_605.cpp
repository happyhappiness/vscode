	    (unpack_unreachable || (pack_everything & LOOSEN_UNREACHABLE)))
		die(_("--keep-unreachable and -A are incompatible"));

	if (pack_kept_objects < 0)
		pack_kept_objects = write_bitmaps;

	packdir = mkpathdup("%s/pack", get_object_directory());
	packtmp = mkpathdup("%s/.tmp-%d-pack", packdir, (int)getpid());

	sigchain_push_common(remove_pack_on_signal);

	argv_array_push(&cmd.args, "pack-objects");
