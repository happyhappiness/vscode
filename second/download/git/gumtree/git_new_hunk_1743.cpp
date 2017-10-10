		base_name = argv[0];
		argc--;
	}
	if (pack_to_stdout != !base_name || argc)
		usage_with_options(pack_usage, pack_objects_options);

	argv_array_push(&rp, "pack-objects");
	if (thin) {
		use_internal_rev_list = 1;
		argv_array_push(&rp, "--objects-edge");
	} else
		argv_array_push(&rp, "--objects");

	if (rev_list_all) {
		use_internal_rev_list = 1;
		argv_array_push(&rp, "--all");
	}
	if (rev_list_reflog) {
		use_internal_rev_list = 1;
		argv_array_push(&rp, "--reflog");
	}
	if (rev_list_index) {
		use_internal_rev_list = 1;
		argv_array_push(&rp, "--indexed-objects");
	}
	if (rev_list_unpacked) {
		use_internal_rev_list = 1;
		argv_array_push(&rp, "--unpacked");
	}

	if (!reuse_object)
		reuse_delta = 0;
	if (pack_compression_level == -1)
		pack_compression_level = Z_DEFAULT_COMPRESSION;
	else if (pack_compression_level < 0 || pack_compression_level > Z_BEST_COMPRESSION)
		die("bad pack compression level %d", pack_compression_level);

	if (!delta_search_threads)	/* --threads=0 means autodetect */
		delta_search_threads = online_cpus();

#ifdef NO_PTHREADS
	if (delta_search_threads != 1)
		warning("no threads support, ignoring --threads");
#endif
	if (!pack_to_stdout && !pack_size_limit)
		pack_size_limit = pack_size_limit_cfg;
