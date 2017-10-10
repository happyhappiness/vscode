		base_name = argv[0];
		argc--;
	}
	if (pack_to_stdout != !base_name || argc)
		usage_with_options(pack_usage, pack_objects_options);

	rp_av[rp_ac++] = "pack-objects";
	if (thin) {
		use_internal_rev_list = 1;
		rp_av[rp_ac++] = "--objects-edge";
	} else
		rp_av[rp_ac++] = "--objects";

	if (rev_list_all) {
		use_internal_rev_list = 1;
		rp_av[rp_ac++] = "--all";
	}
	if (rev_list_reflog) {
		use_internal_rev_list = 1;
		rp_av[rp_ac++] = "--reflog";
	}
	if (rev_list_unpacked) {
		use_internal_rev_list = 1;
		rp_av[rp_ac++] = "--unpacked";
	}

	if (!reuse_object)
		reuse_delta = 0;
	if (pack_compression_level == -1)
		pack_compression_level = Z_DEFAULT_COMPRESSION;
	else if (pack_compression_level < 0 || pack_compression_level > Z_BEST_COMPRESSION)
		die("bad pack compression level %d", pack_compression_level);
#ifdef NO_PTHREADS
	if (delta_search_threads != 1)
		warning("no threads support, ignoring --threads");
#endif
	if (!pack_to_stdout && !pack_size_limit)
		pack_size_limit = pack_size_limit_cfg;
