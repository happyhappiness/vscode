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
		pack_compression_level =