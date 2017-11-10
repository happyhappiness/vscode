int cmd_pack_objects(int argc, const char **argv, const char *prefix)
{
	int use_internal_rev_list = 0;
	int thin = 0;
	int shallow = 0;
	int all_progress_implied = 0;
	struct argv_array rp = ARGV_ARRAY_INIT;
	int rev_list_unpacked = 0, rev_list_all = 0, rev_list_reflog = 0;
	int rev_list_index = 0;
	struct option pack_objects_options[] = {
		OPT_SET_INT('q', "quiet", &progress,
			    N_("do not show progress meter"), 0),
		OPT_SET_INT(0, "progress", &progress,
			    N_("show progress meter"), 1),
		OPT_SET_INT(0, "all-progress", &progress,
			    N_("show progress meter during object writing phase"), 2),
		OPT_BOOL(0, "all-progress-implied",
			 &all_progress_implied,
			 N_("similar to --all-progress when progress meter is shown")),
		{ OPTION_CALLBACK, 0, "index-version", NULL, N_("version[,offset]"),
		  N_("write the pack index file in the specified idx format version"),
		  0, option_parse_index_version },
		OPT_MAGNITUDE(0, "max-pack-size", &pack_size_limit,
			      N_("maximum size of each output pack file")),
		OPT_BOOL(0, "local", &local,
			 N_("ignore borrowed objects from alternate object store")),
		OPT_BOOL(0, "incremental", &incremental,
			 N_("ignore packed objects")),
		OPT_INTEGER(0, "window", &window,
			    N_("limit pack window by objects")),
		OPT_MAGNITUDE(0, "window-memory", &window_memory_limit,
			      N_("limit pack window by memory in addition to object limit")),
		OPT_INTEGER(0, "depth", &depth,
			    N_("maximum length of delta chain allowed in the resulting pack")),
		OPT_BOOL(0, "reuse-delta", &reuse_delta,
			 N_("reuse existing deltas")),
		OPT_BOOL(0, "reuse-object", &reuse_object,
			 N_("reuse existing objects")),
		OPT_BOOL(0, "delta-base-offset", &allow_ofs_delta,
			 N_("use OFS_DELTA objects")),
		OPT_INTEGER(0, "threads", &delta_search_threads,
			    N_("use threads when searching for best delta matches")),
		OPT_BOOL(0, "non-empty", &non_empty,
			 N_("do not create an empty pack output")),
		OPT_BOOL(0, "revs", &use_internal_rev_list,
			 N_("read revision arguments from standard input")),
		{ OPTION_SET_INT, 0, "unpacked", &rev_list_unpacked, NULL,
		  N_("limit the objects to those that are not yet packed"),
		  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1 },
		{ OPTION_SET_INT, 0, "all", &rev_list_all, NULL,
		  N_("include objects reachable from any reference"),
		  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1 },
		{ OPTION_SET_INT, 0, "reflog", &rev_list_reflog, NULL,
		  N_("include objects referred by reflog entries"),
		  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1 },
		{ OPTION_SET_INT, 0, "indexed-objects", &rev_list_index, NULL,
		  N_("include objects referred to by the index"),
		  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1 },
		OPT_BOOL(0, "stdout", &pack_to_stdout,
			 N_("output pack to stdout")),
		OPT_BOOL(0, "include-tag", &include_tag,
			 N_("include tag objects that refer to objects to be packed")),
		OPT_BOOL(0, "keep-unreachable", &keep_unreachable,
			 N_("keep unreachable objects")),
		{ OPTION_CALLBACK, 0, "unpack-unreachable", NULL, N_("time"),
		  N_("unpack unreachable objects newer than <time>"),
		  PARSE_OPT_OPTARG, option_parse_unpack_unreachable },
		OPT_BOOL(0, "thin", &thin,
			 N_("create thin packs")),
		OPT_BOOL(0, "shallow", &shallow,
			 N_("create packs suitable for shallow fetches")),
		OPT_BOOL(0, "honor-pack-keep", &ignore_packed_keep,
			 N_("ignore packs that have companion .keep file")),
		OPT_INTEGER(0, "compression", &pack_compression_level,
			    N_("pack compression level")),
		OPT_SET_INT(0, "keep-true-parents", &grafts_replace_parents,
			    N_("do not hide commits by grafts"), 0),
		OPT_BOOL(0, "use-bitmap-index", &use_bitmap_index,
			 N_("use a bitmap index if available to speed up counting objects")),
		OPT_BOOL(0, "write-bitmap-index", &write_bitmap_index,
			 N_("write a bitmap index together with the pack index")),
		OPT_END(),
	};

	check_replace_refs = 0;

	reset_pack_idx_option(&pack_idx_opts);
	git_config(git_pack_config, NULL);
	if (!pack_compression_seen && core_compression_seen)
		pack_compression_level = core_compression_level;

	progress = isatty(2);
	argc = parse_options(argc, argv, prefix, pack_objects_options,
			     pack_usage, 0);

	if (argc) {
		base_name = argv[0];
		argc--;
	}
	if (pack_to_stdout != !base_name || argc)
		usage_with_options(pack_usage, pack_objects_options);

	argv_array_push(&rp, "pack-objects");
	if (thin) {
		use_internal_rev_list = 1;
		argv_array_push(&rp, shallow
				? "--objects-edge-aggressive"
				: "--objects-edge");
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
	if (pack_to_stdout && pack_size_limit)
		die("--max-pack-size cannot be used to build a pack for transfer.");
	if (pack_size_limit && pack_size_limit < 1024*1024) {
		warning("minimum pack size limit is 1 MiB");
		pack_size_limit = 1024*1024;
	}

	if (!pack_to_stdout && thin)
		die("--thin cannot be used to build an indexable pack.");

	if (keep_unreachable && unpack_unreachable)
		die("--keep-unreachable and --unpack-unreachable are incompatible.");
	if (!rev_list_all || !rev_list_reflog || !rev_list_index)
		unpack_unreachable_expiration = 0;

	if (!use_internal_rev_list || !pack_to_stdout || is_repository_shallow())
		use_bitmap_index = 0;

	if (pack_to_stdout || !rev_list_all)
		write_bitmap_index = 0;

	if (progress && all_progress_implied)
		progress = 2;

	prepare_packed_git();

	if (progress)
		progress_state = start_progress(_("Counting objects"), 0);
	if (!use_internal_rev_list)
		read_object_list_from_stdin();
	else {
		get_object_list(rp.argc, rp.argv);
		argv_array_clear(&rp);
	}
	cleanup_preferred_base();
	if (include_tag && nr_result)
		for_each_ref(add_ref_tag, NULL);
	stop_progress(&progress_state);

	if (non_empty && !nr_result)
		return 0;
	if (nr_result)
		prepare_pack(window, depth);
	write_pack_file();
	if (progress)
		fprintf(stderr, "Total %"PRIu32" (delta %"PRIu32"),"
			" reused %"PRIu32" (delta %"PRIu32")\n",
			written, written_delta, reused, reused_delta);
	return 0;
}